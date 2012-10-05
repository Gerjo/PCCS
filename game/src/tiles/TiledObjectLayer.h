#ifndef TILEDOBJECTLAYER_H
#define TILEDOBJECTLAYER_H

#include <deque>
#include <vector>
#include <math.h>
#include <phantom.h>
#include <layer/EntityLayer.h>
#include "../gameobjects/GameObject.h"

class Tile;

class TiledObjectLayer: public phantom::Layer{
public:
    TiledObjectLayer();
    void createTiles(unsigned int tileSize, unsigned int x, unsigned int y);
    Tile* getTileAt(Vector3 position);
    virtual void addComponent(GameObject* composite);

    int getRowSize();
    int getColumnSize();
    int getSize();

private:
    unsigned int _tileSize, _tilesX, _tilesY;
    Tile** _tileList;
};

#endif /*TILEDOBJECTLAYER_H*/