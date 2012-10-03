#ifndef TILEDOBJECTLAYER_H
#define TILEDOBJECTLAYER_H

#include <deque>
#include <vector>
#include <cmath>
#include <math.h>
#include <algorithm>
#include <layer/ObjectLayer.h>


class Tile;

class TiledObjectLayer: public phantom::ObjectLayer{
public:
    TiledObjectLayer();
    void createTiles(unsigned int tileSize, unsigned int x, unsigned int y);
    Tile* getTileAt(Eigen::Vector3f position);
    virtual void addComponent(phantom::Entity* composite);

    int getRowSize();
    int getColumnSize();
    int getSize();

private:
    unsigned int _tileSize, _tilesX, _tilesY;
    Tile** _tileList;
};

#endif /*TILEDOBJECTLAYER_H*/