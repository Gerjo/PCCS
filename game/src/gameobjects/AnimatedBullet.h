#ifndef ANIMATEDBULLET_H
#define	ANIMATEDBULLET_H

#include "HeavyBullet.h"
#include <sharedlib/gameobjects/LightEnemy.h>
#include <phantom.h>
using namespace phantom;

class AnimatedBullet : public HeavyBullet {
public:
    AnimatedBullet() {
        setType("AnimatedBullet");
    }

    void onCollision(Composite* entity) {    
        if(entity->isType(getType()) || entity->isType("Weapon"))
            return;

        LightEnemy *enemy = dynamic_cast<LightEnemy*>(entity);
        
        if(enemy != nullptr) {
            if(find(_killList.begin(), _killList.end(), string(enemy->name())) == _killList.end())
                return;
        }
        else {
            if(find(_killList.begin(), _killList.end(), string(entity->getType())) == _killList.end())
                return;
        }

        getDriver()->getAudio()->playSound("audio/SFX/explosion.ogg", getPosition());
    }
};

#endif	/* ANIMATEDBULLET_H */
