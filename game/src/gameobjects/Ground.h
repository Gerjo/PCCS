#include <phantom.h>
#include <iostream>
#include <graphics/Color.h>
using namespace phantom;
using namespace std;

#ifndef GROUND_H
#define	GROUND_H


class Ground : public Entity {
public:
    Ground();
    void draw(void);
    virtual void update(const float& elapsed);
private:

};

#endif	/* GROUND_H */

