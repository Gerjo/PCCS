#include <core/Driver.h>
#include <graphics/Graphics.h>

#include "HUD.h"

HUD::HUD() : _actionbarVisible(false), _missionCounterVisible(true), _expandedMissionOverlayVisible(false) {
}

HUD::~HUD() {
}

void HUD::update(const phantom::Time& time) {
    phantom::Composite::update(time);

    phantom::Graphics *g = &getGraphics();

    g->clear();
    if(_actionbarVisible) {
        _actionBar.drawMe(g);
    }
    if(_missionCounterVisible) {
        phantom::Vector3 position = getDriver()->getInput()->getMouseState()->getMousePosition();
        _missionCounter.drawMe(g, &position);
    }
    if(_expandedMissionOverlayVisible) {
        // Draw the expanded mission overlay.
    }
}

void HUD::displayActionBar(bool value) {
    _actionbarVisible = value;
}

void HUD::displayMissionCounter(bool value) {
    _missionCounterVisible = value;
}

void HUD::expandToMissionOverlay(bool value) {
    _expandedMissionOverlayVisible = value;
}