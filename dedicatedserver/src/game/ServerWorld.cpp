#include "ServerWorld.h"
#include "../core/GameHub.h"
#include "../NetworkFactory.h"
#include "../core/PlayerPool.h"
#include <sharedlib/SharedSettings.h>

ServerWorld::ServerWorld(GameHub* gamehub) : _gamehub(gamehub) {

    _root = new BSPTree(SharedSettings::BSP_WIDTH(), SharedSettings::BSP_HEIGHT(), SharedSettings::BSP_SMALLESTSIZE(), SharedSettings::BSP_MAXCOLLISIONSPERSPACE());

    addComponent(_root);
}

ServerWorld::~ServerWorld() {
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

void ServerWorld::update(const Time& time) {
    // Not calling super, I want full control on what happens.
    _commandQueue.run();
    _root->update(time);


}

void ServerWorld::spawnSoldiers(const PlayerModel& model) {
    Data data;

    for(int i = 0; i < 5; ++i) {
        LightSoldier* soldier = static_cast<LightSoldier*>(NetworkFactory::create("soldier"));

        // Bind this soldier to an owner:
        soldier->playerId     = model.id;

        // TODO: Realistic spawn location:
        soldier->setPosition(Vector3(20.0f + i * 50.0f, (40.0f * model.id) + (i * 5.0f), 0.0f));
        addGameObject(soldier);

        soldier->toData(data("dynamic")(soldier->UID_network));
    }

    _gamehub->pool->broadcast(new Packet(PacketType::PUSH_GAMEOBJECTS, data.toJson()), model);
}

void ServerWorld::generate(void) {
    loadPrefab();
    return;
    int width  = static_cast<int>(SharedSettings::BSP_WIDTH());
    int height = static_cast<int>(SharedSettings::BSP_HEIGHT());
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

            //cout << "+ Spawned a " << gameobject->getType() << endl;
        }

    } else {
        cout << "Unable to open './automatically_generated_level.json', the file does not exist." << endl;
    }
}