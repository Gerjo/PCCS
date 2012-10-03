#ifndef TILE_H
#define TILE_H

#include <vector>
#include <phantom.h>
#include <core/Entity.h>
#include <iostream>
#include "TiledObjectLayer.h"

using namespace std;
using namespace phantom;

class Tile {
public: //variables
    std::vector<Entity*> objectList;
    TiledObjectLayer* layer;
public: //functions
    Tile();
    Tile(TiledObjectLayer* layer);
    void addEntity(Entity* entity);
    void removeEntity(Entity* entity);

    void onEntityChange(Entity* entity);
};

#endif /* TILE_H */