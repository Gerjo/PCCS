#include "TiledObjectLayer.h"
#include "Tile.h"
#include <utils/PhantomException.h>
using namespace std;

TiledObjectLayer::TiledObjectLayer():_tileSize(0), _tilesX(0),_tilesY(0){
    _tileList = 0;
}
void TiledObjectLayer::createTiles(unsigned int tileSize, unsigned int x, unsigned int y){
    _tileSize = tileSize;
    _tilesX = x;
    _tilesY = y;

    width = static_cast<float>(x * tileSize);
    height = static_cast<float>(y * tileSize);

    this->width = static_cast<float>(x * _tilesX);
    this->height = static_cast<float>(y* _tilesY);

    _tileList = new Tile*[_tilesY];
    for(y = 0; y < _tilesY; ++y){
        _tileList[y] = new Tile[_tilesX];
        for(x = 0; x < _tilesX; ++x){
            _tileList[y][x] = Tile(this);
        }
    }
}
Tile* TiledObjectLayer::getTileAt(Eigen::Vector3f position) {
    if(_tileList == 0){
        throw PhantomException("Tiles do not exist. Did you call TiledObjectLayer::createTiles()?");
    }
    int x = floor(position.x() / _tileSize);
    int y = floor(position.y() / _tileSize);
    if(x >= _tilesX-1  || y >= _tilesY-1){
        throw PhantomException("EXCEPTION phantom::TiledLayerObject::getTileAt():\nTile array index out of bounds.");
    }
    return &_tileList[y][x];
}
void TiledObjectLayer::addComponent(GameObject* entity){
    Composite::addComponent(entity);
    try{
        Tile* t = getTileAt(entity->getPosition());
        t->addGameObject(entity);
    }catch(PhantomException e){
        cout << e.what() << endl;
        return;
    }
}
int TiledObjectLayer::getRowSize(){
    return _tilesX;
}
int TiledObjectLayer::getColumnSize(){
    return _tilesY;
}
int TiledObjectLayer::getSize(){
    return (_tilesX * _tilesY);
}