#include "ServerWorld.h"
#include "../core/GameHub.h"
#include "../NetworkFactory.h"
#include "../core/PlayerPool.h"
#include "../core/Player.h"
#include <sharedlib/missions/ObjDestroy.h>
#include <sharedlib/services/Services.h>
#include <Procedural.h>

const unsigned int ServerWorld::TREE_AMOUNT = 250;
const unsigned int ServerWorld::ENEMY_AMOUNT = 100;

ServerWorld::ServerWorld(GameHub* gamehub) : _gamehub(gamehub), _proc(nullptr) {
    _root = new BSPTree(
        Services::settings()->bsp_width,
        Services::settings()->bsp_height,
        Services::settings()->bsp_smallestsize,
        Services::settings()->bsp_maxcollisionperspace
        );

    mission = new Mission("first");

    addComponent(_root);
    _root->addComponent(mission);
}

ServerWorld::~ServerWorld()
{
    delete _proc;
    delete _root;
}

void ServerWorld::addGameObject(GameObject* whom) {
    // No need to sync with the update loop, the Composites now have
    // build-in-single-thread-concurrency-protection (tm).
    _root->addComponent(whom);
}

void ServerWorld::selfPipe(Packet* packet) {
    packet->retain();

    string payload = packet->getPayload();

    _commandQueue.add([this, payload] () mutable -> void {
        Data data = Data::fromJson(payload);

        // Reconstruct the message:
        Message<Data>* message = new Message<Data>((string) data("type"), data("payload"));

        // Send it directly to a gameobject:
        GameObject* gameobject = NetworkRegistry::get(data("UID_network").toString());

        if(gameobject == nullptr) {
            cout << "+ Cannot send DIRECT_PIPE message, recipient is unreachable." << endl;
        } else {
            cout << "+ Sending internal DIRECT_PIPE message." << endl;
            gameobject->handleMessage(message);
        }

        delete message;
    });


    packet->release();
}

void ServerWorld::update(const PhantomTime& time) {
    // Not calling super, I want full control on what happens.
    _commandQueue.run();

    _gamehub->playerLock.lock();
    _root->update(time);
    _gamehub->playerLock.unlock();


}

void ServerWorld::generate(void) {
    loadProceduralLevel();
    return;
    int width  = static_cast<int>(Services::settings()->bsp_width);
    int height = static_cast<int>(Services::settings()->bsp_height);
    const int offset = 140;
    srand(23);

    GameObject* crate = NetworkFactory::create("crate");

    crate->setX(100);
    crate->setY(100);

    addGameObject(crate);

    for(float i = 0; i < 1000; ++i) {
        GameObject* magnificentTree = NetworkFactory::create("tree");

        float randomX = static_cast<float>((rand() % (width - offset)) + offset);
        float randomY = static_cast<float>(rand() % height);

        magnificentTree->setX(randomX);
        magnificentTree->setY(randomY);

        addGameObject(magnificentTree);
    }

    for(float i = 0; i < 1000; ++i) {
        GameObject* l33tTank = NetworkFactory::create("tank");

        float randomX = static_cast<float>((rand() % (width - offset)) + offset);
        float randomY = static_cast<float>(rand() % height);

        l33tTank->setX(randomX);
        l33tTank->setY(randomY);

        addGameObject(l33tTank);
    }
}

void ServerWorld::getSerializedDataAsync(Player* player) {
    _commandQueue.add([this, player] {
        Data world = getSerializedData();

        Packet* packet = new Packet(PacketType::REPLY_GAMEWORLD, world.toJson());
        Packet* packetProcedural = new Packet(PacketType::PROCEDURAL, this->_proc->toData().toJson());

        // This is dangerous. We might be working with a dangling pointers here.
        // this is extremely rare though, since when disconnecting, players remain
        // in memory for 7 more seconds. So if the update loop takes longer than
        // 7 seconds, and the player connects, and directly disconnects during that
        // time, the server will *probably* segfault. This solution is OK for
        // now since the old solution crashed even more frequently -- Gerjo.
        player->sendPacket(packet);
        player->sendPacket(packetProcedural);

    });
}

Data ServerWorld::getSerializedData(void) {
    Data data;

    for(Composite* composite : _root->getComponents()) {
        GameObject* gameObject = static_cast<GameObject*>(composite);
        gameObject->toData(data("static")(gameObject->UID_local));
    }

    // Copy might not be so efficient. Change in due time.
    return data;
}

void ServerWorld::loadPrefab(void) {
    File file("automatically_generated_level.json");

    if(file.isFile()) {
        Data data = Data::fromJson(file.readAll());

        for(Data::KeyValue pair : data("dynamic")) {
            Data& info = pair.second;
            GameObject* gameobject = NetworkFactory::create(info("type"));

            gameobject->fromData(info);

            addGameObject(gameobject);

            cout << "+ Spawned a " << gameobject->getType() << endl;
        }

    } else {
        cout << "Unable to open './automatically_generated_level.json', the file does not exist." << endl;
    }
}

void ServerWorld::loadProceduralLevel(){
    if(_proc) delete _proc;
    _proc = new Procedural();
    _proc->generateWorld(5000, 5000, 8, 600);
    _proc->generatePaths(8);

    this->spawnLocations = _proc->spawnLocations;

    createObjectives(*_proc);
    createStaticObjects(*_proc);
    createEnemies(*_proc);
}

float* CreateRandomPosition(float areaSize) {
    int max = (int)(areaSize);
    float* pos = new float[2];
    pos[0] = (float)((rand() % max) - (float)(max * 0.5));
    pos[1] = (float)((rand() % max) - (float)(max * 0.5));

    return pos;
}

void DestroyRandomPosition(float* rand) {
    delete [] rand;
}

void ServerWorld::createObjectives(Procedural& proc) {

}

void ServerWorld::createStaticObjects(Procedural& proc) {
    vector<Center*>& centers = *proc.getCenters(true);
    for(Center* center : centers) {
        Center& c = *center;
        bool neighbourPath = false;
        for(unsigned int i = 0; i < c.neighbours.size(); ++i) {
            if(!c.neighbours[i]->isPath.empty()){ neighbourPath = true; break; }
        }

        if(c.isBorder && c.isPath.size() == 0 && !neighbourPath) {
            GameObject* g;
            for(Edge* edge : c.borders) {
                g = NetworkFactory::create("tree");
                g->setPosition(*edge->v0->point);
                addGameObject(g);
            }
            g = NetworkFactory::create("tree");
            g->setPosition(*c.point);
            addGameObject(g);
            centersWithTree.insert(center);
        }
    }
}

void ServerWorld::createEnemies(Procedural& proc) {
    for(unsigned int i = 0; i < ENEMY_AMOUNT; ++i) {
        Center* c = proc.findRandomNode();
        while(!c->isPath.empty()) {
            otog:
            c = proc.findRandomNode();
        }

        if(centersWithTree.find(c) != centersWithTree.end()) {
            goto otog; // A palindrome, your argument is invalid.
        }

        centersWithTree.insert(c);

        string enemies[] = {
            "Tank", "Robottank", "Trike", "MegaMech", "Rockettrooper", "Sniper", "Tesla", "Helicopter"
        };

        int random = rand() % 8;

        GameObject* g = NetworkFactory::create("Enemy", enemies[random]);

        float* position = CreateRandomPosition(c->getArea());
        g->setPosition(Vector3(c->point->x, c->point->y));
        DestroyRandomPosition(position);

        addGameObject(g);
    }
}