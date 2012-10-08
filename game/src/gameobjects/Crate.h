#ifndef CRATE_H
#define CRATE_H

#include "GameObject.h"

namespace phantom{
    class LIBEXPORT Crate: public GameObject{
    public:
        Crate();
        virtual void onCollision(Composite* other);
        virtual void update(const float& elapsed){}
    private:
        void draw(void);
        bool isVisible;
    };

} /* namespace phantom */

#endif /* CRATE_H */