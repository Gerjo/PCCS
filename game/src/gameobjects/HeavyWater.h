#ifndef HEAVYWATER_H
#define	HEAVYWATER_H

#include <sharedlib/gameobjects/LightWater.h>

using namespace phantom;

class HeavyWater : public LightWater {
public:
    HeavyWater();
    virtual ~HeavyWater();
    virtual void paint(void);
};

#endif	/* HEAVYWATER_H */

