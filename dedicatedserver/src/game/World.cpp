#include "World.h"

#include <sharedlib/factories/LightFactory.h>

World::World() {

}

World::~World() {

}

void World::generate(void) {

    int width  = 2000;
    int height = 2000;

    srand(23);

    for(float i = 0; i < 10000; ++i) {
        GameObject* magnificentTree = LightFactory::create("tree");

        float randomX = static_cast<float>(rand() % width);
        float randomY = static_cast<float>(rand() % width);

        magnificentTree->setX(randomX);
        magnificentTree->setY(randomY);

        _root.addComponent(magnificentTree);
    }
}

Data World::getSerializedData(void) {
    Data data;

    for(Composite* composite : _root.getComponents()) {
        // For now, I'll grab the pointer address as GUID.

        GameObject* gameObject = static_cast<GameObject*>(composite);

        gameObject->toData(data("static")(gameObject->UID_local));
    }

    // Copy might not be so efficient. Change in due time.
    return data;
}