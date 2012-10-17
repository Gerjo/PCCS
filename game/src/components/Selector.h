#ifndef SELECTOR_H
#define	SELECTOR_H

#include <phantom.h>
#include <iostream>
#include "../gameobjects/GameObject.h"
#include "../pathfinding/Pathfinding.h"

using namespace phantom;
using namespace std;

class Game;
class Soldier;

class Selector : public GameObject {
public:
    Selector(BSPTree& layer);
    virtual void update(const float& elapsed);
    void addSoldier(Soldier* soldier);

private:
    bool _hasSelectionStart;
    bool _hasFinalizedSelection;
    bool _doRedraw;
    Game* _game;
    Box3 _selectionBox;
    BSPTree& _layer;
    Camera& _camera;
    deque<Soldier*> _soldiers;

    void handleHover(Vector3& worldLocation, Vector3& screenLocation, MouseState& mouseState);
    void handleSelection(Vector3& worldLocation, Vector3& screenLocation, MouseState& mouseState);
    void drawSelection(void);
    void start(void);
    void finalize();
    void update(void);
    void deSelect(void);
    void click(Vector3& worldLocation, Vector3& screenLocation, MouseState& mouseState);
};

#endif	/* SELECTOR_H */

