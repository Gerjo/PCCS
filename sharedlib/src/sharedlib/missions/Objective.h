#ifndef OBJECTIVE_H_
#define OBJECTIVE_H_

#include <vector>
#include <core/Composite.h>

#include "../../CompileConfig.h"

class LIBEXPORT Objective {
public:
    Objective();
    virtual ~Objective();

    virtual bool conditionsMet() = 0;
    std::vector<phantom::Composite *> *getComposites();

protected:
    /// HINT: PROCEDURAL CONTENT GEN :O
    virtual void generate() { }
    std::vector<phantom::Composite *> _composites;
private:
    
};

#endif
