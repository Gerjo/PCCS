#ifndef OBJECTIVE_H_
#define OBJECTIVE_H_

#include <phantom.h>
#include <vector>
#include <core/Composite.h>

#include "../CompileConfig.h"
#include "../gameobjects/GameObject.h"

using namespace phantom;

class LIBEXPORT Objective : public GameObject {
public:
    Objective(string title);
    virtual ~Objective();

    virtual void setConditions() = 0;
    virtual bool conditionsMet() = 0;
    string getTitle();
    std::vector<GameObject *> *getComposites();
    bool wasMore;

    bool forcedComplete;
protected:
    /// HINT: PROCEDURAL CONTENT GEN :O
    virtual void generate() { }
    std::vector<GameObject*> _objects;
    unsigned int difficulty;
    string _title;
private:
    
};

#endif
