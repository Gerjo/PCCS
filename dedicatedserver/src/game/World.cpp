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
