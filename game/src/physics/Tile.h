#ifndef TILE_H
#define TILE_H

#include <vector>
#include <phantom.h>
#include <core/Entity.h>

using namespace std;
using namespace phantom;

class Tile {
public: //variables
    std::vector<phantom::Entity*> objectList;
    int index, tileX, tileY;
public: //functions
    Tile();
    virtual ~Tile();
    void addEntity(phantom::Entity* entity);
    void removeEntity(phantom::Entity* entity);


};

#endif /* TILE_H */