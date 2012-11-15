#include "MenuButton.h"

MenuButton::MenuButton() : _isBusy(false) {
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
        image("images/menu/button1.png", 0.0f, 0.0f, getBoundingBox().size.x, getBoundingBox().size.y).
        fill().
        setFillStyle(phantom::Colors::BLACK).
        text((getBoundingBox().size.x / 2) - ((_text.size() * fontSize) / 3), (getBoundingBox().size.y / 2) - fontSize, fontSize, "fonts/waree.ttf", _text).
        fill();
}

void MenuButton::onClick(MouseState *mousestate) {
    // Temp hack against buttom spam.
    if(!_isBusy) {
        _isBusy = true;
        onClickFunction();
    }
    
}