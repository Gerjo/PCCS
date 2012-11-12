#ifndef LIGHTCRATE_H
#define LIGHTCRATE_H

#include <string>
#include <algorithm>
#include "GameObject.h"
#include "behaviours/AbstractBehaviour.h"

class LIBEXPORT LightCrate : public GameObject{
public:
    LightCrate();
    virtual void toData(Data& data);
    virtual void fromData(Data& data);
    virtual void update(const Time& time);
    virtual void onCollision(Composite* entity);

private:
    AbstractBehaviour* createFromString(string typeName);
    AbstractBehaviour* _content;
};

#endif /* LIGHTCRATE_H */