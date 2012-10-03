#ifndef WATER_H_
#define WATER_H_
#include <phantom.h>
#include "../gameobjects/GameObject.h"

using namespace phantom;

class Water : public GameObject {
public:
    Water();
    ~Water();

    virtual void update(float elapsed);
private:
    void draw();
};

#endif // !WATER_H_
