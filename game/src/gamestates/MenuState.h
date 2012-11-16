#ifndef MENU_H_
#define MENU_H_

#include <phantom.h>
#include "../guicomponents/menu/MainMenu.h"
#include "../guicomponents/menu/SettingsMenu.h"
#include "../guicomponents/menu/ServerBrowser.h"
#include "../guicomponents/menu/CreditsMenu.h"

class MenuState : public phantom::GameState
{
public:
    MenuState();
    ~MenuState();

    void navigate(string to);

private:
    MainMenu *_mainMenu;
    SettingsMenu *_settingsMenu;
    ServerBrowser *_serverBrowser;
    CreditsMenu *_creditsMenu;

    string _location;
};

#endif
