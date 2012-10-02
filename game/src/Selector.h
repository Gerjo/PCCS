#ifndef SELECTOR_H
#define	SELECTOR_H

#include <phantom.h>
#include <iostream>

using namespace phantom;
using namespace Eigen;
using namespace std;

class Selector : public Entity {
public:
    Selector();
    virtual void update(const float& elapsed);

private:
    void draw(void);
    Vector3f _start;
    Vector3f _end;

    bool _hasStartPoint;

};

#endif	/* SELECTOR_H */

