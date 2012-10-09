#ifndef SOLDIER_H
#define	SOLDIER_H

#include <phantom.h>
#include <iostream>
#include "../gameobjects/GameObject.h"
#include "../pathfinding/Pathfinding.h"


using namespace phantom;
using namespace std;

class Soldier : public GameObject {
public:
    Soldier();
    virtual void onCollision(Composite* other);
    virtual void update(const float& elapsed);
    void setSelected(bool isSelected);
    void setTarget(Vector3 target);
    bool isSelected(void);

    void setPath(vector<Vector3*> path);

private:
    void draw(void);

    Vector3 _target;
    bool _isSelected;
    bool _hasCollision;
    bool _newCollisionState;
    vector<Vector3*> _path;
    bool _showPath;
    bool _doRedraw;
};

#endif	/* SOLDIER_H */

