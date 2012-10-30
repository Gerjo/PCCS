#ifndef LIGHTSOLDIER_H
#define	LIGHTSOLDIER_H

#include <phantom.h>
#include "GameObject.h"
#include "../CompileConfig.h"
#include "../pathfinding/Pathfinding.h"

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

    virtual void update(const Time& time);
    virtual void fromData(Data& data);
    virtual void toData(Data& data);
    virtual MessageState handleMessage(AbstractMessage* message);

    void onKillSomething(GameObject* gameobject);
    int getPlayerId(void);

    int playerId;
    LightWeapon* weapon;

protected:
    virtual void init(void);
    vector<Vector3> _path; // For debugging only.
    GameObject* _victim;

    bool seekRoute(Vector3 location);
    void handleAi(void);
};

#endif	/* LIGHTSOLDIER_H */

