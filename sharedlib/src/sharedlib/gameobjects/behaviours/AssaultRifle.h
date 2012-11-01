#ifndef ASSAULT_H
#define ASSAULT_H

#include "WeaponBehaviour.h"

class LIBEXPORT AssaultRifle : public WeaponBehaviour{
public:
    AssaultRifle();
    virtual void render(void);

protected:
  
};


#endif /* ASSAULT_H */