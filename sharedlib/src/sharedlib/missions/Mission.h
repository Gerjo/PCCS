#ifndef MISSION_H_
#define MISSION_H_

#include <vector>
#include <phantom.h>
#include "../gameobjects/GameObject.h"
#include "../CompileConfig.h"

#include "Objective.h"

using namespace phantom;

class LIBEXPORT Mission : public GameObject{
public:
    Mission(const std::string& title);
    virtual ~Mission();

    void addObjective(Objective *objectiveID);
    void removeObjective(Objective *objectiveID);
    void checkIfCompleted();
    virtual void update(const Time& time);
    virtual void fromData(Data& data);
    virtual void toData(Data& data);

protected:
    virtual bool missionComplete();

private:
    std::vector<Objective*> _objectives;
    std::vector<Objective*> _objectivesCompleted;
};

#endif
