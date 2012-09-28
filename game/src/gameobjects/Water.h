#ifndef WATER_H_
#define WATER_H_
#include <core\Entity.h>

class Water : public phantom::Entity
{
public:
    Water();
    ~Water();

    virtual void update(float elapsed);
private:
    void draw();
};

#endif // !WATER_H_
