#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <phantom.h>
#include <sharedlib/serialization/Data.h>
#include <sharedlib/networking/UID.h>
#include "../ClickableEntity.h"
#include "../CompileConfig.h"

using namespace phantom;

class LIBEXPORT GameObject : public Entity {
public:
    GameObject();
    ~GameObject();
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

    UID::Type UID_network;
    UID::Type UID_local;

    float getHealth() { return _health; }
    float getTotalHealth() { return _totalHealth; }

    // Expirimental. The Factory should set this flag.
    enum ResidenceState { CLIENT, SERVER };
    ResidenceState residence;

protected:
    bool _canHover;
};

#endif /* GAMEOBJECT_H */