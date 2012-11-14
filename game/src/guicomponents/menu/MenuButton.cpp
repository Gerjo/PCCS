#include "MenuButton.h"

MenuButton::MenuButton() {
    addComponent(new Clicktor());

    setBoundingBox(Box3(0.0f, 0.0f, 807.0f, 136.0f));
}

MenuButton::~MenuButton() {
}

void MenuButton::setText(std::string text) {
    _text = text;
}

void MenuButton::paint() {
    int fontSize = 48;

    getGraphics().clear().beginPath().setFillStyle(phantom::Colors::WHITE).
        image("images/menu/button1.png", 0.0f, 0.0f, 807.0f, 136.0f).
        fill().
        setFillStyle(phantom::Colors::BLACK).
        text(403.5f - ((_text.size() * fontSize) / 3), 20.0f, fontSize, "fonts/waree.ttf", _text).
        fill();
}

void MenuButton::onClick(MouseState *mousestate) {
    onClickFunction();
}