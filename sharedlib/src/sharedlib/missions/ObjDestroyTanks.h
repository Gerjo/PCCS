#ifndef OBJDESTROYTANKS_H_

#include <vector>

#include "Objective.h"
#include "../gameobjects/LightTank.h"

class LIBEXPORT ObjDestroyTanks : public Objective {
public:
    ObjDestroyTanks();
    ~ObjDestroyTanks();

    virtual void setConditions(){}
    bool conditionsMet();

protected:

private:
    std::vector<LightTank*> _tanks;
};

#endif // !OBJDESTROYTANKS_H_
