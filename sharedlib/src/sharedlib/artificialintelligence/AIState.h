#ifndef AISTATE_H_
#define AISTATE_H_

#include "CompileConfig.h"
#include <utils/Time.h>
#include <phantom.h>


class GameObject;
class ArtificialIntelligence;

using namespace phantom;

class LIBEXPORT AIState : public IHandleMessage, public IUpdateable {
public:
    ArtificialIntelligence* ai;


    AIState();
    virtual void construct();
    virtual void destruct();
    virtual MessageState handleMessage(AbstractMessage* message);
    virtual void update(const phantom::PhantomTime& time) = 0;
    bool isEnabled();

protected:
    GameObject* getOwner();

private:
    bool _isEnabled;
};

#endif