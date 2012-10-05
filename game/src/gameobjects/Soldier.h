#ifndef SOLDIER_H
#define	SOLDIER_H

#include <phantom.h>
#include <iostream>
#include "../gameobjects/GameObject.h"

using namespace phantom;
using namespace std;

class Soldier : public GameObject {
public:
    Soldier();

    virtual void update(const float& elapsed);

    void setSelected(bool isSelected);

    void setTarget(Vector3 target);
    bool isSelected(void);
private:
    void draw(void);

    Vector3 _velocity;
    Vector3 _target;

    bool _isSelected;
};

#endif	/* SOLDIER_H */

