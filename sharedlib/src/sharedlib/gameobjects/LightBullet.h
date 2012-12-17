#ifndef LIGHTBULLET_H
#define	LIGHTBULLET_H

#include <phantom.h>
#include "GameObject.h"
#include "LightSoldier.h"
#include "behaviours/BulletBehaviour.h"
#include "../CompileConfig.h"
#include <vector>

using namespace phantom;
using std::vector;

class LightSoldier;

class LIBEXPORT LightBullet : public GameObject {
public:
    LightBullet();
    virtual ~LightBullet();
    void setBehaviour(BulletBehaviour* newBehaviour);

    virtual void update(const PhantomTime& time);
    virtual void fromData(Data& data);
    virtual void toData(Data& data);
    virtual void onDestruction();
    void setDirection(Vector3& direction);
    void setAuthority(bool hasAutority);

    GameObject* owner;
    virtual void killList(vector<string> killList);

protected:
    BulletBehaviour* _bulletBehaviour;
    Vector3 _velocity;
    double _creationTime;
    double _ttl;
    float _damage;
    bool _hasAuthority;
    vector<string> _killList;

};

#endif	/* LIGHTBULLET_H */
