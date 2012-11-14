#ifndef ROCKET_H
#define ROCKET_H

#include "BulletBehaviour.h"

class LIBEXPORT Rocket : public BulletBehaviour{
public:
    Rocket();
    virtual void onCollision(Composite* entity);
    virtual void render(Graphics* g);
    void onDestroy(Graphics* g);
};


#endif /* ROCKET_H */