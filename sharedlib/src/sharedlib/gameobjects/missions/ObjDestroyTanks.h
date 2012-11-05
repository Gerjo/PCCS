#ifndef OBJDESTROYTANKS_H_

#include <vector>

#include "Objective.h"
#include "../LightTank.h"

class LIBEXPORT ObjDestroyTanks : public Objective {
public:
    ObjDestroyTanks();
    ~ObjDestroyTanks();

    bool conditionsMet();

protected:

private:
    std::vector<LightTank*> _tanks;
};

#endif // !OBJDESTROYTANKS_H_
