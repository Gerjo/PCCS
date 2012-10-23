#include "World.h"

#include <sharedlib/gameobjects/LightTree.h>

World::World() {

}

World::~World() {

}

void World::generate(void) {

    for(float i = 1; i < 11; ++i) {
        LightTree* magnificentTree = new LightTree();

        magnificentTree->setPosition(Vector3(i * 100, i * 100, 0.0f));

        _root.addComponent(magnificentTree);
    }
}

Data World::getSerializedData(void) {
    Data data;

    for(Composite* composite : _root.getComponents()) {
        // For now, I'll grab the pointer address as GUID.
        stringstream key;
        key << composite->getType();
        key << ":" << composite;

        static_cast<GameObject*>(composite)->toData(data(key.str()));

    }

    // Copy might be so efficient. Ahh well.
    return data;
}