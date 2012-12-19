#ifndef ENEMYMIXIN_H_
#define ENEMYMIXIN_H_

#include "../CompileConfig.h"
#include "GameObject.h"

class LIBEXPORT EnemyMixin {
public:
    EnemyMixin(GameObject *me);

    virtual void move(const Vector3& location) = 0;
    void attack(GameObject *victim);
    void shootAt(UID::Type uid);
    void stopShooting();
    bool hasVictim();
    GameObject *getVictim();
    bool isAttacking();

protected:
    GameObject *_victim;
    bool _isAttacking;
    
private:
    GameObject *_me;
};

#endif