#ifndef OBJDESTROY_H_
#define OBJDESTROY_H_
#include <vector>

#include "Objective.h"
#include "../gameobjects/LightTank.h"
#include "../gameobjects/GameObject.h"

class LIBEXPORT ObjDestroy : public Objective {
public:
    ObjDestroy(string title);
    ~ObjDestroy();
    void addObject(GameObject* gob);
    virtual void setConditions();
    bool conditionsMet();

protected:

private:
    std::vector<LightTank*> _tanks;
    int _objectCounter;
};

#endif // !OBJDESTROY_H_
