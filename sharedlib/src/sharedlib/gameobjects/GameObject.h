#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <phantom.h>
#include <cmath>
#include <sharedlib/serialization/Data.h>
#include <sharedlib/networking/UID.h>
#include "../CompileConfig.h"

using namespace phantom;

class Services;
class Squad;
class ArtificialIntelligence;

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
    enum ResidenceState { CLIENT = 1, SERVER = 2, BOTH = 3 };
    ResidenceState residence;

    void registerDestoryEvent(IHandleMessage* subscribee);
    void unregisterDestoryEvent(IHandleMessage* subscribee);

    virtual void destroy(void);

    bool hasSquad(void);
    Squad* squad;

    ArtificialIntelligence* ai;
protected:
    bool _canHover;
    float _health;
    float _totalHealth;
    vector<string> _killList;

    virtual void setHealth(float value);

private:
    std::deque<IHandleMessage*> _destroyListeners;
};

#endif /* GAMEOBJECT_H */