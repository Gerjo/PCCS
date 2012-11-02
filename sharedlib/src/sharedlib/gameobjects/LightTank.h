#ifndef LIGHTTANK_H_
#define LIGHTTANK_H_

#include <sharedlib/gameobjects/GameObject.h>

class LIBEXPORT LightTank : public GameObject {
public:
    LightTank();
    virtual ~LightTank();

    virtual void attack(GameObject* victim);
    virtual void update(const Time& time);
};

#endif