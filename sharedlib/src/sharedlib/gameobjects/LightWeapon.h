#ifndef LIGHTWEAPON_H
#define	LIGHTWEAPON_H

#include <phantom.h>
#include "GameObject.h"
#include "LightBullet.h"
#include "../CompileConfig.h"
#include <iostream>

using namespace phantom;
using std::cout;
using std::endl;

class LIBEXPORT LightWeapon : public GameObject {
public:
    LightWeapon();
    virtual ~LightWeapon();

    virtual LightBullet* createBullet();

    float getRange(void);
    float getRangeSq(void);
    bool isCooldownExpired(void);
    void startCooldown(void);

protected:
    float _range;
    double _cooldownTimeSeconds;
    double _lastShootTime;
};

#endif	/* LIGHTWEAPON_H */
