#include <graphics/Graphics.h>

#include "HUD.h"

HUD::HUD() : _actionbarVisible(false), _missionCounterVisible(false), _expandedMissionOverlayVisible(false) {
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
        _missionCounter.drawMe(g);
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