#include <graphics/Graphics.h>

#include "HUD.h"

HUD::HUD() : _actionbarVisible(true), _missionCounterVisible(false), _expandedMissionOverlayVisible(false), _hasChanges(true) {
}

HUD::~HUD() {
}

void HUD::update(const phantom::Time& time) {
    phantom::Composite::update(time);

    if(_hasChanges) {
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

        _hasChanges = false;
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