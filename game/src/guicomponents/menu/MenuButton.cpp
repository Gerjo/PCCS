#include "MenuButton.h"

MenuButton::MenuButton() {
    addComponent(new Clicktor());
}

MenuButton::~MenuButton() {
}

void MenuButton::setText(std::string text) {
    _text = text;
}

void MenuButton::paint() {
}
