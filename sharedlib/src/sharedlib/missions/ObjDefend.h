#ifndef OBJDEFEND_H
#define OBJDEFEND_H

#include "Objective.h"
#include <phantom.h>

using phantom::Timer;

class LIBEXPORT ObjDefend: public Objective{
public:
    ObjDefend(GameObject* target, string title);
    ~ObjDefend();
    virtual void update(const PhantomTime& time);
    virtual void setConditions();
    virtual bool conditionsMet();
private:
    GameObject* _target;
    Timer timer;
    float ttl;
    bool _isDefending;
};

#endif /* OBJDEFEND_H */