#ifndef HEAVYTANKMECH_H_
#define HEAVYTANKMECH_H_

#include <sharedlib/gameobjects/LightTankMech.h>

class HeavyTankMech : public LightTankMech {
public:
    HeavyTankMech();
    ~HeavyTankMech();

    void update(const phantom::PhantomTime &time);
    void paint();
    void attack(GameObject *victim);
    void move(const Vector3& location);
    void onMouseHover(const Vector3& mouseLocationWorld, const Vector3& mouseLocationScreen);
    void fromData(Data &data);
    void toData(Data& data);
private:
    Vector3 _directionTur;
};

#endif // !HEAVYTANKMECH_H_
