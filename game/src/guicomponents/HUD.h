#ifndef HUD_H_
#define HUD_H_

#include <core/Composite.h>

#include "ActionBar.h"
#include "MissionCounter.h"

class HUD : public phantom::Composite {
public:
    HUD();
    ~HUD();

    void displayActionBar(bool value);
    void displayMissionCounter(bool value);
    void expandToMissionOverlay(bool value);

    void update(const phantom::Time& time);

private:
    bool _actionbarVisible;
    bool _missionCounterVisible;
    bool _expandedMissionOverlayVisible;
    bool _hasChanges;

    ActionBar _actionBar;
    MissionCounter _missionCounter;
};
#endif // !HUD_H_
