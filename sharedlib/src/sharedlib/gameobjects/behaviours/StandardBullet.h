#ifndef STANDARDBULLET_H
#define STANDARDBULLET_H

#include <common/CompileConfig.h>
#include "../GameObject.h"
#include "BulletBehaviour.h"

class LIBEXPORT StandardBullet : public BulletBehaviour{
public:
    StandardBullet();
    virtual void onCollision(Composite* entity);
    virtual void render(Graphics* g);
protected:
};

#endif /* STANDARDBULLET_H */ 