#include "MenuState.h"

MenuState::MenuState() : _location("") {
    _mainMenu = nullptr;
    _settingsMenu = nullptr;
    navigate("/");
}

MenuState::~MenuState() {
}

void MenuState::navigate(string to) {
    if(to == "/") {
        _mainMenu = new MainMenu();
        addComponent(_mainMenu);
    }
    else if(to == "settings") {
        _settingsMenu = new SettingsMenu();
        addComponent(_settingsMenu);
    }

    if(_location == "/") {
        _mainMenu->destroy();
        _mainMenu = nullptr;
    }
    else if(_location == "settings") {
        _settingsMenu->destroy();
        _settingsMenu = nullptr;
    }

    _location = to;
}