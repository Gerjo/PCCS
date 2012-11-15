#include "MenuInputField.h"

void MenuInputField::paint() {
    getGraphics().beginPath().setFillStyle(Colors::WHITE).image("images/menu/button1.png", 0.0f, 0.0f, getBoundingBox().size.x, getBoundingBox().size.y).fill();
}
