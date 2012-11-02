#ifndef ASSAULT_H
#define ASSAULT_H

#include "WeaponBehaviour.h"

class LIBEXPORT AssaultRifle : public WeaponBehaviour{
public:
    AssaultRifle();
    virtual void render(phantom::Graphics* g);
protected:
    void setType();
};


#endif /* ASSAULT_H */