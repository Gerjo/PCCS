#include "MenuInputField.h"

void MenuInputField::paint() {
    getGraphics().clear().beginPath().
        setFillStyle(phantom::Colors::WHITE).image("images/menu/button1.png", -10.0f, 0.0f, getBoundingBox().size.x, getBoundingBox().size.y).fill();
}
