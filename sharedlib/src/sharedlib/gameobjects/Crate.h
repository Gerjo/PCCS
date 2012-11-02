#ifndef CRATE_H
#define CRATE_H

#include <string>
#include <algorithm>
#include "GameObject.h"
#include "behaviours/AbstractBehaviour.h"

class LIBEXPORT Crate : public GameObject{
public:
    Crate();
    virtual void toData(Data& data);
    virtual void fromData(Data& data);
    virtual void update(const Time& time);
private:
    AbstractBehaviour* createFromString(string typeName);
    AbstractBehaviour* _content;
};

#endif /* CRATE_H */