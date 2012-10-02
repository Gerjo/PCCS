#ifndef SOLDIER_H
#define	SOLDIER_H

#include <phantom.h>
#include <iostream>

using namespace phantom;
using namespace std;
using namespace Eigen;

class Soldier : public Entity {
public:
    Soldier();

    virtual void update(const float& elapsed);

    void setSelected(bool isSelected);

    void setTarget(Vector3f target);
    bool isSelected(void);
private:
    void draw(void);

    Vector3f _velocity;
    Vector3f _target;

    bool _isSelected;
};

#endif	/* SOLDIER_H */

