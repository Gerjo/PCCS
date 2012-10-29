#include "ServerWorld.h"
#include "../core/GameHub.h"
#include "../NetworkFactory.h"
#include "../core/PlayerPool.h"


ServerWorld::ServerWorld(GameHub* gamehub) : _gamehub(gamehub) {
    _root = new BSPTree(Settings::BSP_WIDTH, Settings::BSP_HEIGHT, Settings::BSP_SMALLESTSIZE, Settings::BSP_MAXCOLLISIONSPERSPACE);
}

ServerWorld::~ServerWorld() {
    delete _root;
}

void ServerWorld::broadcast(Packet* packet) {
    packet->retain();
    cout << "+ self packet." << endl;
    packet->release();
}

void ServerWorld::run() {
    cout << "+ Starting world physics thread." << endl;

    double last  = Util::getTime();
    double total = 0.0f;
    int fpscount = 0;
    const int debuginterval = 10;

    do {
        double now = Util::getTime();
        double elapsed = now - last;
        total += elapsed;

        Time time(static_cast<float>(elapsed), static_cast<float>(total), now);
        _root->update(time);

        fpscount++;

        if (total >= debuginterval) {
            cout << "+ Physics running at " << (fpscount/debuginterval) << " iterations per second. " << endl;
            fpscount = 0;
            total    = 0;
        }

        last = now;
        sleep(10);
    } while(true);

    //_root->update();
}

void ServerWorld::spawnSoldier(const PlayerModel& model) {
    LightSoldier* soldier = static_cast<LightSoldier*>(NetworkFactory::create("soldier"));

    // Bind this soldier to an owner:
    soldier->playerId     = model.id;

    // TODO: Realistic spawn location:
    soldier->setPosition(Vector3(100.0f, 20.0f * model.id, 0.0f));
    _root->addComponent(soldier);

    // TODO: push update to all connected players.
    Data data;
    soldier->toData(data("dynamic")(soldier->UID_network));

    _gamehub->pool->broadcast(new Packet(PacketType::PUSH_GAMEOBJECTS, data.toJson()), model);
}

void ServerWorld::generate(void) {

    int width  = Settings::BSP_WIDTH;
    int height = Settings::BSP_HEIGHT;
    const int offset = 140.0f;
    srand(23);

    for(float i = 0; i < 1000; ++i) {
        GameObject* magnificentTree = NetworkFactory::create("tree");

        float randomX = static_cast<float>((rand() % (width - offset)) + offset);
        float randomY = static_cast<float>(rand() % height);

        magnificentTree->setX(randomX);
        magnificentTree->setY(randomY);

        _root->addComponent(magnificentTree);
    }
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