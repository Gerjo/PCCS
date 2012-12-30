#include "MenuButton.h"

MenuButton::MenuButton(float x, float y, float width, float height) : Button(x, y, width, height) {
}

MenuButton::~MenuButton() {
}

void MenuButton::paint() {
    int fontSize = 48;

    getGraphics().clear().beginPath().setFillStyle(phantom::Colors::WHITE).
        image("images/menu/button1.png", 0.0f, 0.0f, getBoundingBox().size.x, getBoundingBox().size.y).
        fill().
        setFillStyle(phantom::Colors::BLACK).
        text((getBoundingBox().size.x / 2) - ((text().size() * fontSize) / 3), (getBoundingBox().size.y / 2) - fontSize, fontSize, "fonts/waree.ttf", text()).
        fill();
}