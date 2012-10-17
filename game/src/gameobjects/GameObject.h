#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <core/Entity.h>

using namespace phantom;

class GameObject : public Entity {
public:
    GameObject();
    bool canHover(void);
    virtual void onMouseHover(const Vector3& mouseLocationWorld, const Vector3& mouseLocationScreen);
    virtual void onSelect(void);
    virtual void onDeselect(void);

    float distanceTo(GameObject* gob);
    float distanceToSq(GameObject* gob);

protected:
    bool _canHover;
    
};

#endif /* GAMEOBJECT_H */