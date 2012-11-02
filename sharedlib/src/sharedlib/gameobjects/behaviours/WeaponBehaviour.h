#ifndef WEAPONBEHAVIOUR_H
#define WEAPONBEHAVIOUR_H

#include <phantom.h>
#include <common/CompileConfig.h>
#include "AbstractBehaviour.h"

class LIBEXPORT WeaponBehaviour : public AbstractBehaviour {
public:
    
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
    virtual void render(phantom::Graphics* g) =0;

protected:
    float _rateOfFire;
    float _range;
    double _cooldownTimeSeconds;
    double _lastShootTime;
};


#endif /* WEAPONBEHAVIOUR_H */