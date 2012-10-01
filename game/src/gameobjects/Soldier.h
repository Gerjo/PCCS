#ifndef SOLDIER_H
#define	SOLDIER_H

#include <phantom.h>
#include <iostream>

using namespace phantom;
using namespace std;

class Soldier : public Entity {
public:
    Soldier();
private:
    void draw(void);
};

#endif	/* SOLDIER_H */

