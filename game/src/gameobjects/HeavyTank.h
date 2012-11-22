#ifndef HEAVYTANK_H_
#define HEAVYTANK_H_

#include <sharedlib/gameobjects/LightTank.h>

class HeavyTank : public LightTank {
public:
    HeavyTank();
    ~HeavyTank();

    void paint();
    void attack(GameObject *victim);
private:
    Vector3 _directionTur;
};

#endif // !HEAVYTANK_H_
