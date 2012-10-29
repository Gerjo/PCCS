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

void ServerWorld::run() {
    double last  = Util::getTime();
    double total = 0.0f;
    int fpscount = 0;

    do {
        double now = Util::getTime();
        double elapsed = now - last;
        total += elapsed;

        Time time(static_cast<float>(elapsed), static_cast<float>(total), now);
        _root->update(time);

        fpscount++;

        if (total >= 1) {
            cout << "+ [Avg FPS: " << fpscount << " Cur FPS: " << 1.0f / elapsed << "]" << endl;
            fpscount = 0;
            total    = 0;
        }

        last = now;
        sleep(100);
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

    srand(23);

    for(float i = 0; i < 1000; ++i) {
        GameObject* magnificentTree = NetworkFactory::create("tree");

        float randomX = static_cast<float>(rand() % width);
        float randomY = static_cast<float>(rand() % width);

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