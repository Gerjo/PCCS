#include "GameObject.h"
#include "../tiles/Tile.h"

GameObject::GameObject(){
    _tile = 0;
}
void GameObject::setX(float x){
    Entity::setX(x);
    if(hasTile()){
       // _tile->onGameObjectChange(this);
    }
}
void GameObject::setY(float y){
    Entity::setY(y);
    if(hasTile()){
       // _tile->onGameObjectChange(this);
    }
}
void GameObject::setTile(Tile* tile){
    _tile = tile;
}
Tile* GameObject::getTile(){
    if(hasTile()){
        return _tile;
    }
}
bool GameObject::hasTile(){
    return _tile != 0;
}