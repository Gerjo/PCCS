#include "World.h"

#include <sharedlib/factories/LightFactory.h>

World::World() {

}

World::~World() {

}

void World::generate(void) {

    for(float i = 1; i < 11; ++i) {
        GameObject* magnificentTree = LightFactory::create("tree");

        magnificentTree->setPosition(Vector3(i * 100, i * 100, 0.0f));

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