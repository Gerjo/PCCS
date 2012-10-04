#include <phantom.h>
#include <iostream>
#include <graphics/Color.h>
#include "../gameobjects/GameObject.h"

using namespace phantom;
using namespace std;

#ifndef GROUND_H
#define	GROUND_H

class Ground : public GameObject {
public:
    Ground();
    void draw(void);
    virtual void update(const float& elapsed);
private:

};

#endif	/* GROUND_H */

