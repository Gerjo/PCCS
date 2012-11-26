#ifndef HEAVYHELICOPTER_H_
#define HEAVYHELICOPTER_H_

#include <sharedlib/gameobjects/LightHelicopter.h>

class HeavyHelicopter : public LightHelicopter
{
public:
    HeavyHelicopter();
    ~HeavyHelicopter();

    void update(const phantom::PhantomTime &time);
    void paint();
    void attack(GameObject *victim);
    void fly(Vector3 location);
    void onMouseHover(const Vector3 &mouseLocationWorld, const Vector3 &mouseLocationScreen);

private:
    int _rotorblade;
    vector<string> _killList;
};

#endif

