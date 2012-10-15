#ifndef SOLDIER_H
#define	SOLDIER_H

#include <phantom.h>
#include <iostream>
#include "../gameobjects/GameObject.h"
#include "../pathfinding/Pathfinding.h"
#include "../goodies/weapons/Weapon.h"

using namespace phantom;
using namespace std;

class Soldier : public GameObject {
public:
    Soldier();
    virtual void onCollision(Composite* other);
    virtual void update(const float& elapsed);
    void setSelected(bool isSelected);
    bool isSelected(void);

    // Override from game object:
    virtual void onMouseHover(const Vector3& mouseLocationWorld, const Vector3& mouseLocationScreen);
    virtual void onSelect(void);
    virtual void onDeselect(void);

    void attack(GameObject* victim);
    void walk(Vector3 location);
    void setShowPath(bool isVisible);

private:
    void draw(void);
    void handleAi(void);
    void seekRoute(Vector3 location);

    GameObject* _victim;
    Weapon* _weapon;
    bool _isSelected;
    bool _hasCollision;
    bool _newCollisionState;
    vector<Vector3> _path;
    bool _showPath;
    bool _doRedraw;
    bool _isHovering;
};

#endif	/* SOLDIER_H */

