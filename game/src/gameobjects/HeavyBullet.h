#ifndef HEAVYBULLET_H
#define	HEAVYBULLET_H

#include <phantom.h>
#include <sharedlib/gameobjects/LightBullet.h>

using namespace phantom;

class HeavyBullet : public LightBullet {
public:
    HeavyBullet();
    virtual ~HeavyBullet();
    virtual void update(const Time& time);
private:

};

#endif	/* HEAVYBULLET_H */
