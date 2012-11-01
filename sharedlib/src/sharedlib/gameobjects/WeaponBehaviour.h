#ifndef WEAPONBEHAVIOUR_H
#define WEAPONBEHAVIOUR_H

#include <phantom.h>
#include <common/CompileConfig.h>

class LIBEXPORT WeaponBehaviour{
public:
    WeaponBehaviour(): _rateOfFire(20), _range(20), _cooldownTimeSeconds(1), _lastShootTime(0){

    }
    virtual float getRange(void){
        return _range;
    }
    virtual float getRangeSq(void){
        return _range * _range;
    }
    virtual bool isCoolDownExpired(void){
        const double now = phantom::Util::getTime();
        return now - _lastShootTime > _cooldownTimeSeconds;
    }
    virtual void startCoolDown(void) {
        _lastShootTime = phantom::Util::getTime();
    }
    virtual void render(void) =0;

protected:
    float _rateOfFire;
    float _range;
    double _cooldownTimeSeconds;
    double _lastShootTime;
};


#endif /* WEAPONBEHAVIOUR_H */