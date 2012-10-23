#ifndef TILE_H
#define TILE_H

#include <vector>
#include <phantom.h>
#include <sharedlib/gameobjects/GameObject.h>
#include <iostream>
#include "TiledObjectLayer.h"

using namespace std;
using namespace phantom;

class Tile {
public: //variables
    std::vector<GameObject*> objectList;
    TiledObjectLayer* layer;
public: //functions
    Tile();
    Tile(TiledObjectLayer* layer);
    void addGameObject(GameObject* entity);
    void removeGameObject(GameObject* entity);

    void onGameObjectChange(GameObject* entity);
};

#endif /* TILE_H */