#ifndef STANDARDBULLET_H
#define STANDARDBULLET_H

#include <common/CompileConfig.h>
#include "BulletBehaviour.h"

class LIBEXPORT StandardBullet : public BulletBehaviour{
public:
    StandardBullet();
    virtual void onCollision(Composite* entity);

};

#endif /* STANDARDBULLET_H */ 