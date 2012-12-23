#ifndef LIGHTENEMY_H_
#define LIGHTENEMY_H_

#include "GameObject.h"
#include "EnemyMixin.h"
#include "LightWeapon.h"
#include "../CompileConfig.h"
#include "../serialization/Data.h"

class AIState;
class LIBEXPORT LightEnemy : public GameObject, public EnemyMixin {
public:
    LightWeapon *weapon;
    
    LightEnemy(Data enemyinfo);
    ~LightEnemy();

    void move(const Vector3& location);
    MessageState handleMessage(AbstractMessage *message);
    void fromData(Data &data);
    void toData(Data &data);
    string name();

protected:
    Data _initialEnemyInfo;

private:
    vector<AIState *> _AIstates;
    bool _movethrough;

    void insertAndActivateInAI(AIState *state);
};


#endif