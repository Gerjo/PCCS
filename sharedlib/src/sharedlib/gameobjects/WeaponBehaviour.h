#ifndef WEAPONBEHAVIOUR_H
#define WEAPONBEHAVIOUR_H

#include <phantom.h>
#include <common/CompileConfig.h>

class LIBEXPORT WeaponBehaviour{
public:
    virtual float getRange(void) = 0;
    virtual float getRangeSq(void) = 0;
    virtual bool isCoolDownExpired(void){
        const double now = phantom::Util::getTime();
        return now - _lastShootTime > _cooldownTimeSeconds;
    }
    virtual void startCoolDown(void) {
        _lastShootTime = phantom::Util::getTime();
    }

protected:
    float _rateOfFire;
    float _range;
    double _cooldownTimeSeconds;
    double _lastShootTime;
};


#endif /* WEAPONBEHAVIOUR_H */