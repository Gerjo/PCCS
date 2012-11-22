#include "HeavyTrigger.h"

HeavyTrigger::HeavyTrigger() : LightTrigger() {
    paint();
}

void HeavyTrigger::paint() {
#ifdef _DEBUG
    getGraphics().clear().beginPath().setFillStyle(phantom::Colors::RED).
        moveTo(-10.0f, -10.0f).
        lineTo(10.0f, 10.0f).fill().
        moveTo(10.0f, -10.0f).
        lineTo(-10.0f, 10.0f).fill();
#endif
}