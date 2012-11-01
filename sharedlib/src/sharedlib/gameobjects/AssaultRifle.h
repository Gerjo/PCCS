#ifndef ASSAULT_H
#define ASSAULT_H

#include "WeaponBehaviour.h"

class LIBEXPORT AssaultRifle : public WeaponBehaviour{
public:
    AssaultRifle(): _rateOfFire(20), _range(20), _cooldownTimeSeconds(1), _lastShootTime(0){

    }

    virtual void render(void);
protected:
    float _rateOfFire;
    float _range;
    double _cooldownTimeSeconds;
    double _lastShootTime;
};


#endif /* ASSAULT_H */