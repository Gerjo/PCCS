#ifndef OBJDESTROY_H_
#define OBJDESTROY_H_
#include <vector>

#include "Objective.h"
#include "../gameobjects/GameObject.h"
#include "../gameobjects/LightEnemy.h"

class LIBEXPORT ObjDestroy : public Objective {
public:
    ObjDestroy(string title);
    ~ObjDestroy();
    void addObject(GameObject* gob);
    virtual void setConditions();
    virtual void addComponent(Composite* composite);
    bool conditionsMet();

protected:

private:
    std::vector<LightEnemy*> _tanks;
    int _objectCounter;
};

#endif // !OBJDESTROY_H_
