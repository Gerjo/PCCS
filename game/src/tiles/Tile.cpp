#include "Tile.h"

Tile::Tile(){}

Tile::Tile(TiledObjectLayer* layer) {
    this->layer = layer;
}
void Tile::addGameObject(GameObject* entity) {
    objectList.push_back(entity);
    //cout << "addGameObject! adding tile" << endl;

}
void Tile::removeGameObject(GameObject* entity){
    std::vector<GameObject*>::iterator it =  objectList.begin();
    while(it != objectList.end()){
        if((*it) == entity){
            objectList.erase(it);

            return;
        }
        ++it;
    }
}

void Tile::onGameObjectChange(GameObject* entity) {
    Tile* t = layer->getTileAt(entity->getPosition());
    if( t != this){
        //cout << "OnGameObjectChange! removing tile" << endl;
        removeGameObject(entity);
        t->addGameObject(entity);
    }
}