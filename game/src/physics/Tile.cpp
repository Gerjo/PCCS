#include "Tile.h"

Tile::Tile(){
}
Tile::~Tile(){
}
void Tile::addEntity(phantom::Entity* entity){
    objectList.push_back(entity);
}
