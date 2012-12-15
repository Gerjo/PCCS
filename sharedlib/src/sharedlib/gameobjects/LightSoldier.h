#ifndef LIGHTSOLDIER_H
#define	LIGHTSOLDIER_H

#include <phantom.h>
#include "GameObject.h"
#include "../CompileConfig.h"
#include "../pathfinding/Pathfinding.h"
#include "LightBullet.h"
#include <sharedlib/networking/UID.h>
#include <sharedlib/serialization/DataHelper.h>

using namespace phantom;

using std::string;
using std::cout;
using std::endl;

class LightWeapon;
class LightBullet;

class LIBEXPORT LightSoldier : public GameObject {
public:
    LightSoldier();
    virtual ~LightSoldier();

    virtual void update(const PhantomTime& time);
    virtual void fromData(Data& data);
    virtual void toData(Data& data);
    virtual MessageState handleMessage(AbstractMessage* message);
    virtual void onCollision(Composite* other, CollisionData& collisionData);
    virtual bool canShootAt(Entity* gameobject);

    int playerId;
    LightWeapon* weapon;

    bool isSquadLeader();
protected:
    Pathfinding::Route _path; // For debugging only.
    GameObject* _victim;

};

#endif	/* LIGHTSOLDIER_H */

