#ifndef OBJDESTROYTANKS_H_
#define OBJDESTROYTANKS_H_
#include <vector>

#include "Objective.h"
#include "../gameobjects/LightTank.h"
#include "../gameobjects/GameObject.h"

class LIBEXPORT ObjDestroyTanks : public Objective {
public:
    ObjDestroyTanks(string title);
    ~ObjDestroyTanks();
    void addObject(GameObject* gob);
    virtual void setConditions();
    bool conditionsMet();

protected:

private:
    std::vector<LightTank*> _tanks;
};

#endif // !OBJDESTROYTANKS_H_
