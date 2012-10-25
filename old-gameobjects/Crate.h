#ifndef CRATE_H
#define CRATE_H

#include <sharedlib/gameobjects/GameObject.h>

class Crate: public GameObject{
public:
    Crate();
    virtual void onCollision(Composite* other);
    virtual void update(const float& elapsed){}
private:
    void draw(void);
    bool isVisible;
};

#endif /* CRATE_H */