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

    // Override from gameobject:
    virtual void onMouseHover(const Vector3& mouseLocationWorld, const Vector3& mouseLocationScreen);
    virtual void onSelect(void);
    virtual void onDeselect(void);
private:
    void draw(void);

    Vector3 _target;
    bool _isSelected;
    bool _hasCollision;
    bool _newCollisionState;
    vector<Vector3*> _path;
    bool _showPath;
    bool _doRedraw;
    bool _isHovering;
};

#endif	/* SOLDIER_H */

