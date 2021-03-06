#ifndef HEAVYWEAPON_H
#define	HEAVYWEAPON_H

#include <phantom.h>
#include <sharedlib/gameobjects/LightWeapon.h>

using namespace phantom;

class HeavyWeapon : public LightWeapon {
public:
    HeavyWeapon();
    virtual ~HeavyWeapon();

    virtual LightBullet* createBullet();
private:

};

#endif	/* HEAVYWEAPON_H */
