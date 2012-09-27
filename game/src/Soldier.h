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

    int x;
    int y;

    bool isMovingRight;

};

#endif	/* SOLDIER_H */

