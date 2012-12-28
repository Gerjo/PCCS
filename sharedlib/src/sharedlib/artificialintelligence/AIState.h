#ifndef AISTATE_H_
#define AISTATE_H_

#include "CompileConfig.h"
#include <utils/Time.h>
#include <phantom.h>

class GameObject;
class ArtificialIntelligence;

using namespace phantom;

class LIBEXPORT AIState : public IHandleMessage {
public:
    ArtificialIntelligence* ai;
    bool isEnabled;

    AIState();
    virtual void construct();
    virtual void destruct();
    virtual MessageState handleMessage(AbstractMessage* message);
    virtual void handle(const phantom::PhantomTime& time) = 0;

private:
    GameObject* getOwner();
    
};

#endif