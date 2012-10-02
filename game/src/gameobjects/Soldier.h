#ifndef SOLDIER_H
#define	SOLDIER_H

#include <phantom.h>
#include <iostream>

using namespace phantom;
using namespace std;


class Soldier : public Entity {
public:
    Soldier();

    virtual void update(const float& elapsed);

private:
    void draw(void);

    Eigen::Vector3f _velocity;

};

#endif	/* SOLDIER_H */

