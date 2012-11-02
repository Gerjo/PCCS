#ifndef HEAVYTANK_H_
#define HEAVYTANK_H_

#include <sharedlib/gameobjects/LightTank.h>

class HeavyTank : public LightTank {
public:
    HeavyTank();
    ~HeavyTank();

    void paint();
private:
    Vector3 _directionTur;
    Vector3 _direction;
};

#endif // !HEAVYTANK_H_