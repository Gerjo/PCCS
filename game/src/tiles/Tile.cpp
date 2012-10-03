#include "Tile.h"

Tile::Tile(){}

Tile::Tile(TiledObjectLayer* layer) {
    this->layer = layer;
}
void Tile::addEntity(phantom::Entity* entity) {
    objectList.push_back(entity);
    //cout << "addEntity! adding tile" << endl;

}
void Tile::removeEntity(Entity* entity){
    std::vector<Entity*>::iterator it =  objectList.begin();
    while(it != objectList.end()){
        if((*it) == entity){
            objectList.erase(it);

            return;
        }
        ++it;
    }
}

void Tile::onEntityChange(Entity* entity) {
    Tile* t = layer->getTileAt(entity->getPosition());
    if( t != this){
        //cout << "OnEntityChange! removing tile" << endl;
        removeEntity(entity);
        t->addEntity(entity);
    }
}