#ifndef WALKSTATE_H
#define	WALKSTATE_H

#include "../AIState.h"
#include <phantom.h>
#include "../../CompileConfig.h"

using namespace phantom;


// tmp:
#include <iostream>
using std::cout;
using std::endl;

class LIBEXPORT SquadMove : public AIState {
public:
    SquadMove();

    void setTarget(const Vector3& target);
    virtual void construct();
    virtual void update(const phantom::PhantomTime& time);
    virtual void destruct();

private:
    Vector3 _target;
};

#endif	/* WALKSTATE_H */
