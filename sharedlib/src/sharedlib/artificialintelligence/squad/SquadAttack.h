#ifndef SQUADATTACK_H
#define	SQUADATTACK_H

#include "../../CompileConfig.h"
#include "../AIState.h"
#include <phantom.h>
#include <vector>

using namespace phantom;
using std::vector;

class GameObject;

// tmp:
#include <iostream>
using std::cout;
using std::endl;



class LIBEXPORT SquadAttack : public AIState {
public:
    SquadAttack();
    ~SquadAttack();
    void setVictim(GameObject* gameobject);
    virtual void construct();
    virtual void handle(const phantom::PhantomTime& time);
    virtual MessageState handleMessage(AbstractMessage* message);
    virtual void destruct();

private:
    void resetVictim(void);

    GameObject* _victim;
    Timer _updateInterval;
};

#endif	/* SQUADATTACK_H */

