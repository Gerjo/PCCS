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

    phantom::MouseState *mousestate = getDriver()->getInput()->getMouseState();

    g->clear();
    if(_actionbarVisible) {
        _actionBar.drawMe(g, mousestate);
    }
    if(_missionCounterVisible) {
        _missionCounter.drawMe(g, &mousestate->getPosition());
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