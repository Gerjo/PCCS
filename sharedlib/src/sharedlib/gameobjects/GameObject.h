#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <phantom.h>
#include <cmath>
#include <sharedlib/serialization/Data.h>
#include <sharedlib/networking/UID.h>
#include "../CompileConfig.h"
#include "../services/Services.h"
#include "../pathfinding/SolidStateBits.h"

using namespace phantom;


class LIBEXPORT GameObject : public Entity {
public:
    GameObject();
    ~GameObject();
    bool canHover(void);
    virtual void onMouseHover(const Vector3& mouseLocationWorld, const Vector3& mouseLocationScreen);
    virtual void onClick(MouseState *mousestate);
    virtual void onUnClicked(MouseState *mousestate);
    virtual void onSelect(void);
    virtual void onDeselect(void);
    virtual void onDestruction(void);
    virtual bool removeHealth(float amount);

    float distanceTo(GameObject* gob);
    float distanceToSq(GameObject* gob);
    Vector3 directionTo(GameObject* gob);

    virtual void paint(void);
    void repaint(void);

    virtual MessageState handleMessage(AbstractMessage* message);
    virtual void fromData(Data& data);
    virtual void toData(Data& data);

    UID::Type UID_network;
    UID::Type UID_local;

    float getHealth() { return _health; }
    float getTotalHealth() { return _totalHealth; }

    // Experimental. The NetworkFactory will set this flag.
    enum ResidenceState { CLIENT, SERVER };
    ResidenceState residence;

    void registerDestoryEvent(GameObject* subscribee);
    void unregisterDestoryEvent(GameObject* subscribee);
    virtual void onGameObjectDestroyed(GameObject* destroyedGameObject);
    virtual void destroy(void);

protected:
    bool _canHover;
    float _health;
    float _totalHealth;


    virtual void setHealth(float value);

private:
    std::deque<GameObject*> _destroyListeners;
};

#endif /* GAMEOBJECT_H */