#ifndef ENEMY_H
#define ENEMY_H

#include "GameObject.h"
#include "Soldier.h"

namespace phantom{
    class LIBEXPORT Enemy: public GameObject{
    public:
        Enemy();
        virtual void onCollision(Composite* other);
        virtual void update(const float& elapsed);
    private:
        void draw();
        bool attack;
        Soldier* target;
        Entity searchArea;
    };

} /* namespace phantom */

#endif /*ENEMY_H */