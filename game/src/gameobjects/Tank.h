#ifndef TANK_H_
#define TANK_H_
#include <phantom.h>
#include "../gameobjects/GameObject.h"
using namespace phantom;

class Tank : public GameObject {
public:
    Tank();
    ~Tank();

    virtual void update(float elapsed);
private:
    void draw();
};

#endif // !TANK_H_
