#ifndef SQUADATTACK_H
#define	SQUADATTACK_H



#include "../../CompileConfig.h"
#include "../AIState.h"
#include <phantom.h>

using namespace phantom;

// tmp:
#include <iostream>
using std::cout;
using std::endl;

class GameObject;

class LIBEXPORT SquadAttack : public AIState {
public:
    SquadAttack();
    virtual ~SquadAttack();
    void setVictim(GameObject* gameobject);
    virtual void construct();
    virtual void handle(const phantom::PhantomTime& time);
    virtual MessageState handleMessage(AbstractMessage* message);
    virtual void destruct();

private:
    GameObject* _victim;
    Timer _updateInterval;
};

#endif	/* SQUADATTACK_H */

