#ifndef ENEMY_H
#define ENEMY_H

#include "GameObject.h"
#include "Soldier.h"

namespace phantom{
    class Enemy: public GameObject{
    public:
        Enemy();
        virtual void onCollision(Composite* other);
        virtual void update(const float& elapsed);
    private:
        float offset;
        void attack(Soldier* soldier);
        void draw();
        bool isAttacking;
        Soldier* _target ;
        Entity searchArea;
    };

} /* namespace phantom */

#endif /*ENEMY_H */