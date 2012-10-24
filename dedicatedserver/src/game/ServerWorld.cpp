#include "ServerWorld.h"

#include <sharedlib/factories/LightFactory.h>

ServerWorld::ServerWorld() {

}

ServerWorld::~ServerWorld() {

}

void ServerWorld::spawnSoldier(const PlayerModel& model) {
    LightSoldier* soldier = static_cast<LightSoldier*>(LightFactory::create("soldier"));

    // Bind this soldier to an owner:
    soldier->playerId     = model.id;

    // TODO: Realistic spawn location:
    soldier->setPosition(Vector3(100.0f, 20.0f * model.id, 0.0f));

    _root.addComponent(soldier);

    // TODO: push update to all connected players.
}

void ServerWorld::generate(void) {

    int width  = 2000;
    int height = 2000;

    srand(23);

    for(float i = 0; i < 1000; ++i) {
        GameObject* magnificentTree = LightFactory::create("tree");

        float randomX = static_cast<float>(rand() % width);
        float randomY = static_cast<float>(rand() % width);

        magnificentTree->setX(randomX);
        magnificentTree->setY(randomY);

        _root.addComponent(magnificentTree);
    }
}

Data ServerWorld::getSerializedData(void) {
    Data data;

    for(Composite* composite : _root.getComponents()) {
        GameObject* gameObject = static_cast<GameObject*>(composite);
        gameObject->toData(data("static")(gameObject->UID_local));
    }

    // Copy might not be so efficient. Change in due time.
    return data;
}