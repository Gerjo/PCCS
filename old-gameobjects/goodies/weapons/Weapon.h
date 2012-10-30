#ifndef GUN_H
#define	GUN_H

#include <phantom.h>
#include <cmath>
#include "../bullets/Bullet.h"
#include "../../components/Console.h"
#include <sstream>

using namespace std;
using namespace phantom;

class Weapon : public Composite {
public:
    Weapon(void);
    string getName(void);
    float getRange(void);
    float getRangeSq(void);
    virtual Bullet* createBullet(Entity* owner);

    bool isCooldownExpired(void);
    void startCooldown(void);

protected:
    float _range;
    string _name;
    double _cooldownTimeSeconds;
    double _lastShootTime;
};

#endif	/* GUN_H */

