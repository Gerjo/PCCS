#ifndef LIGHTSOLDIER_H
#define	LIGHTSOLDIER_H

#include <phantom.h>
#include "GameObject.h"
#include "../CompileConfig.h"
#include "../pathfinding/Pathfinding.h"
#include "LightBullet.h"
#include <sharedlib/networking/UID.h>

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

    virtual void attack(GameObject* victim);
    virtual void walk(Vector3 location);

    virtual void update(const PhantomTime& time);
    virtual void fromData(Data& data);
    virtual void toData(Data& data);
    virtual MessageState handleMessage(AbstractMessage* message);
    virtual void onCollision(Composite* other);
    virtual bool canShootAt(Entity* gameobject);

    int playerId;
    LightWeapon* weapon;

    // Experimental:
    void formationFollow(LightSoldier* leader);
    void formationLeadTheWay(LightSoldier* leader);

protected:
    void shootAt(UID::Type uid);
    void stopShooting();

    virtual void onBulletFired(LightBullet* bullet);

    Pathfinding::Route _path; // For debugging only.
    GameObject* _victim;

    bool seekRoute(Vector3 location);


};

#endif	/* LIGHTSOLDIER_H */

