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
    Selector(BSPTree& layer);
    virtual void update(const float& elapsed);

    void addSoldier(Soldier* soldier);

private:
    void handleHover(Vector3& worldLocation, Vector3& screenLocation, MouseState& mouseState);
    void handleSelection(Vector3& worldLocation, Vector3& screenLocation, MouseState& mouseState);

    void drawSelection(void);
    Box3 _selectionBox;
    bool _hasSelectionStart;
    bool _hasFinalizedSelection;
    bool _doRedraw;

    BSPTree& _layer;
    Camera& _camera;

    deque<Soldier*> _soldiers;

    void start(void);
    void finalize();
    void update(void);
    void deSelect(void);
    void click(Vector3& worldLocation, Vector3& screenLocation, MouseState& mouseState);
    string _hoverText;
};

#endif	/* SELECTOR_H */

