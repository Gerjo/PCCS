#ifndef SELECTOR_H
#define	SELECTOR_H

#include <phantom.h>
#include <iostream>

using namespace phantom;
using namespace Eigen;
using namespace std;

class Soldier;

class Selector : public Entity {
public:
    Selector();
    virtual void update(const float& elapsed);

    void addSoldier(Soldier* soldier);

private:
    void draw(void);
    Vector3f _startpoint;
    Vector3f _endpoint;

    bool _hasStartpoint;

    deque<Soldier*> _soldiers;

    void start(void);
    void finalize();
    void update(void);
    void cancel(void);
};

#endif	/* SELECTOR_H */

