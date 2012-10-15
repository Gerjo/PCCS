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
        virtual void onMouseHover(const Vector3& mouseLocationWorld, const Vector3& mouseLocationScreen);

    private:
        void draw();
        bool _isMouseHover;
        bool _doRedraw;
    };

} /* namespace phantom */

#endif /*ENEMY_H */