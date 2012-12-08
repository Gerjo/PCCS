#ifndef HEAVYOBSTACLE_H
#define	HEAVYOBSTACLE_H


#include <sharedlib/gameobjects/LightTree.h>

using namespace phantom;

class HeavyObstacle : public LightTree {
public:
    HeavyObstacle(float rotation);
    virtual ~HeavyObstacle();
    virtual void paint(void);
private:
    string imageChar;
};

#endif	/* HEAVYOBSTACLE_H */

