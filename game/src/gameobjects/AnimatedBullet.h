#ifndef ANIMATEDBULLET_H
#define	ANIMATEDBULLET_H

#include "HeavyBullet.h"

#include <phantom.h>
using namespace phantom;

class AnimatedBullet : public HeavyBullet {
public:
    AnimatedBullet() {
        setType("AnimatedBullet");
    }

    void onCollision(Composite* entity) {
        // Doing absolutely nothing.
    }
};

#endif	/* ANIMATEDBULLET_H */
