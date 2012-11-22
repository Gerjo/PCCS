#ifndef HEAVYTANK_H_
#define HEAVYTANK_H_

#include <sharedlib/gameobjects/LightTank.h>

class HeavyTank : public LightTank {
public:
    HeavyTank();
    ~HeavyTank();

    void update(const phantom::Time &time);
    void paint();
    void attack(GameObject *victim);
    void fromData(Data &data);
    void toData(Data& data);
private:
    Vector3 _directionTur;
};

#endif // !HEAVYTANK_H_
