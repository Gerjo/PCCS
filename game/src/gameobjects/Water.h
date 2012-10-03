#ifndef WATER_H_
#define WATER_H_
#include <phantom.h>

using namespace phantom;

class Water : public Entity {
public:
    Water();
    ~Water();

    virtual void update(float elapsed);
private:
    void draw();
};

#endif // !WATER_H_
