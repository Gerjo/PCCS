#include <core/Driver.h>
#include <graphics/Graphics.h>

#include "HUD.h"

HUD::HUD() : _actionbarVisible(false), _missionCounterVisible(true) {
    _actionBar      = new ActionBar();
    _missionCounter = new MissionCounter();

    addComponent(_actionBar);
    addComponent(_missionCounter);

    _missionCounter->missions.push_back("Destroy tanks");
    _missionCounter->missions.push_back("Kill snipers in the forest");
}

HUD::~HUD() {
}

void HUD::update(const phantom::PhantomTime& time) {
    phantom::Composite::update(time);

    _actionBar->visible         = _actionbarVisible;
    _missionCounter->visible    = _missionCounterVisible;
}

void HUD::displayActionBar(bool value) {
    _actionbarVisible = value;
}

void HUD::displayMissionCounter(bool value) {
    _missionCounterVisible = value;
}