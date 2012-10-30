#ifndef LIGHTWEAPON_H
#define	LIGHTWEAPON_H

#include <phantom.h>
#include "GameObject.h"
#include "LightBullet.h"

using namespace phantom;

class LightWeapon : public GameObject {
public:
    LightWeapon();
    virtual ~LightWeapon();

    virtual LightBullet* createBullet();
private:

};

#endif	/* LIGHTWEAPON_H */
