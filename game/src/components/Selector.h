#ifndef SELECTOR_H
#define	SELECTOR_H

#include <phantom.h>
#include <iostream>
#include "../gameobjects/GameObject.h"
#include "../pathfinding/Pathfinding.h"

using namespace phantom;
using namespace std;

class Soldier;

class Selector : public GameObject {
public:
    Selector();
    virtual void update(const float& elapsed);

    void addSoldier(Soldier* soldier);

private:
    void drawSelection(void);
    Box3 _world;

    bool _hasSelectionStart;
    bool _hasFinalizedSelection;

    deque<Soldier*> _soldiers;

    void start(void);
    void finalize();
    void update(void);
    void cancel(void);
    void click(void);
};

#endif	/* SELECTOR_H */

