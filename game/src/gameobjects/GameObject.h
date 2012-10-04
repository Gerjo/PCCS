#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <core/Entity.h>


using namespace phantom;

class Tile;
class GameObject : public Entity {
public:
    GameObject();
    virtual void setX(float x);
    virtual void setY(float y);

    void setTile(Tile* tile);
    void removeTile();
    Tile* getTile();
    bool hasTile();

private:
    Tile* _tile;

};

#endif /* GAMEOBJECT_H */