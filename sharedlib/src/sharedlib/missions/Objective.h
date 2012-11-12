#ifndef OBJECTIVE_H_
#define OBJECTIVE_H_

#include <phantom.h>
#include <vector>
#include <core/Composite.h>

#include "../CompileConfig.h"
#include "../gameobjects/GameObject.h"

using namespace phantom;

class LIBEXPORT Objective : public Composite {
public:
    Objective(string title);
    virtual ~Objective();

    virtual void setConditions() = 0;
    virtual bool conditionsMet() = 0;
    std::vector<GameObject *> *getComposites();

protected:
    /// HINT: PROCEDURAL CONTENT GEN :O
    virtual void generate() { }
    std::vector<GameObject*> _objects;
    string _title;
private:
    
};

#endif
