#ifndef LIGHTWEAPON_H
#define	LIGHTWEAPON_H

#include <phantom.h>
#include "GameObject.h"
#include "LightBullet.h"
#include "../CompileConfig.h"
#include <iostream>
#include "behaviours/WeaponBehaviour.h"

using namespace phantom;
using std::cout;
using std::endl;

class LIBEXPORT LightWeapon : public GameObject {
public:
    LightWeapon();
    virtual ~LightWeapon();

    virtual LightBullet* createBullet();

    void setWeaponBehaviour(WeaponBehaviour* newBehaviour);
    float getRange(void);
    float getRangeSq(void);
    bool isCooldownExpired(void);
    void startCooldown(void);

protected:
    float _range;
    double _cooldownTimeSeconds;
    double _lastShootTime;
    WeaponBehaviour* _weaponBehaviour;
};

#endif	/* LIGHTWEAPON_H */
