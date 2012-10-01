#ifndef TANK_H_
#define TANK_H_
#include <core/Entity.h>

class Tank : public phantom::Entity
{
public:
    Tank();
    ~Tank();

    virtual void update(float elapsed);
private:
    void draw();
};

#endif // !TANK_H_
