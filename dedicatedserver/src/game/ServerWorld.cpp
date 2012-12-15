#include "ServerWorld.h"
#include "../core/GameHub.h"
#include "../NetworkFactory.h"
#include "../core/PlayerPool.h"
#include "../core/Player.h"
#include <sharedlib/missions/ObjDestroy.h>
#include <sharedlib/services/Services.h>

ServerWorld::ServerWorld(GameHub* gamehub) : _gamehub(gamehub){
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

    _root->update(time);


}

void ServerWorld::generate(void) {
    loadPrefab();
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

        // This is dangerous. We might be working with a dangling pointers here.
        // this is extremely rare though, since when disconnecting, players remain
        // in memory for 7 more seconds. So if the update loop takes longer than
        // 7 seconds, and the player connects, and directly disconnects during that
        // time, the server will *probably* segfault. This solution is OK for
        // now since the old solution crashed even more frequently -- Gerjo.
        player->sendPacket(packet);
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
        ObjDestroy* obj = new ObjDestroy("Destroy all tanks!");
        Data data = Data::fromJson(file.readAll());
        for(Data::KeyValue pair : data("dynamic")) {
            Data& info = pair.second;

            if(info("type").toString() != "Tree" && info("type").toString() != "Soldier") {
                continue;
            }

            GameObject* gameobject = NetworkFactory::create(info("type"));
            gameobject->fromData(info);

            //cout << "+ Spawned a " << gameobject->getType() << endl;
            addGameObject(gameobject);
        }
    } else {
        cout << "Unable to open './automatically_generated_level.json', the file does not exist." << endl;
    }
}