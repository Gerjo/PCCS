#ifndef TILEDOBJECTLAYER_H
#define TILEDOBJECTLAYER_H

#include <deque>
#include <vector>
#include <math.h>
#include <phantom.h>
#include <layer/ObjectLayer.h>
#include "../gameobjects/GameObject.h"

class Tile;

class TiledObjectLayer: public phantom::ObjectLayer{
public:
    TiledObjectLayer();
    void createTiles(unsigned int tileSize, unsigned int x, unsigned int y);
    Tile* getTileAt(Eigen::Vector3f position);
    virtual void addComponent(GameObject* composite);

    int getRowSize();
    int getColumnSize();
    int getSize();

private:
    unsigned int _tileSize, _tilesX, _tilesY;
    Tile** _tileList;
};

#endif /*TILEDOBJECTLAYER_H*/