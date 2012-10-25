#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <core/Entity.h>
#include <sharedlib/serialization/Data.h>
#include <sharedlib/networking/UID.h>
#include "../CompileConfig.h"

using namespace phantom;

class LIBEXPORT GameObject : public Entity {
public:
    GameObject();
    bool canHover(void);
    virtual void onMouseHover(const Vector3& mouseLocationWorld, const Vector3& mouseLocationScreen);
    virtual void onSelect(void);
    virtual void onDeselect(void);

    float distanceTo(GameObject* gob);
    float distanceToSq(GameObject* gob);
    Vector3 directionTo(GameObject* gob);

    virtual void paint(void);
    void repaint(void);

    virtual void fromData(Data& data);
    virtual void toData(Data& data);

    string UID_network;
    const string UID_local;
protected:
    bool _canHover;

};

#endif /* GAMEOBJECT_H */