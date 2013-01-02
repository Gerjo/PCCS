#ifndef HEAVYENEMY_H_
#define HEAVYENEMY_H_

#include "../helper/ImageDirections.h"
#include "../guicomponents/HealthBar.h"
#include <sharedlib/gameobjects/LightEnemy.h>

class HeavyEnemy : public LightEnemy {
public:
    HeavyEnemy(Data enemyinfo);
    void update(const phantom::PhantomTime &time);
    void paint();
    void repaint();
    void move(const Vector3 &location);
    void fromData(Data& data);
    void onMouseHover(const Vector3& mouseLocationWorld, const Vector3& mouseLocationScreen);

private:
    float _width;
    float _height;
    PhantomTime _time;
    bool _requiresRedraw;
    vector<Data> _images;
};

#endif // !HEAVYENEMY_H_
