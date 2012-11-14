#include "MenuState.h"

MenuState::MenuState() : _location("/") {
    _mainMenu = new MainMenu();
    addComponent(_mainMenu);
}

MenuState::~MenuState() {
}

void MenuState::navigate(string to) {
    _location.append(to);
}