#ifndef TANK_H_
#define TANK_H_
#include <phantom.h>

using namespace phantom;

class Tank : public Entity
{
public:
    Tank();
    ~Tank();

    virtual void update(float elapsed);
private:
    void draw();
};

#endif // !TANK_H_
