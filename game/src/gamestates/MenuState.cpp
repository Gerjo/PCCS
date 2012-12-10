#include "MenuState.h"

MenuState::MenuState() : _location("") {
    _mainMenu = new MainMenu();
    _settingsMenu = new SettingsMenu();
    serverBrowser = new ServerBrowser();
    _creditsMenu = new CreditsMenu();

    navigate("join");
}

MenuState::~MenuState() {
    removeLocationFromParent();

    delete _mainMenu;       _mainMenu = nullptr;
    delete _settingsMenu;   _settingsMenu = nullptr;
    delete serverBrowser;   serverBrowser = nullptr;
    delete _creditsMenu;    _creditsMenu = nullptr;
}

void MenuState::navigate(string to) {
    if(to == "/") {
        addComponent(_mainMenu);
    }
    else if(to == "settings") {
        addComponent(_settingsMenu);
    }
    else if(to == "join") {
        addComponent(serverBrowser);
    }
    else if(to == "credits") {
        addComponent(_creditsMenu);
    }

    removeLocationFromParent();

    _location = to;
}

void MenuState::removeLocationFromParent() {
    if(_location == "/") {
        _mainMenu->removeFromParent();
    }
    else if(_location == "settings") {
        _settingsMenu->removeFromParent();
    }
    else if(_location == "join") {
        serverBrowser->removeFromParent();
    }
    else if(_location == "credits") {
        _creditsMenu->removeFromParent();
    }
}