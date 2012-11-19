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
    else if(to == "join") {
        _serverBrowser = new ServerBrowser();
        addComponent(_serverBrowser);
    }
    else if(to == "credits") {
        _creditsMenu = new CreditsMenu();
        addComponent(_creditsMenu);
    }

    if(_location == "/") {
        _mainMenu->destroy();
        _mainMenu = nullptr;
    }
    else if(_location == "settings") {
        _settingsMenu->destroy();
        _settingsMenu = nullptr;
    }
    else if(_location == "join") {
        _serverBrowser->destroy();
        _serverBrowser = nullptr;
    }
    else if(_location == "credits") {
        _creditsMenu->destroy();
        _creditsMenu = nullptr;
    }

    _location = to;
}