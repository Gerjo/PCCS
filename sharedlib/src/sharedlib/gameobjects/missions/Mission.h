#ifndef MISSION_H_
#define MISSION_H_

#include <vector>

#include "../../CompileConfig.h"
#include "Objective.h"

class LIBEXPORT Mission {
public:
    Mission();
    virtual ~Mission();

    void addObjective(Objective *objectiveID);
    void removeObjective(Objective *objectiveID);
    void checkIfCompleted();

protected:
    virtual bool missionComplete();

private:
    std::vector<Objective*> _objectives;
    std::vector<Objective*> _objectivesCompleted;
};

#endif
