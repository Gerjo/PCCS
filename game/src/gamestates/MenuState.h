#ifndef MENU_H_
#define MENU_H_

#include <phantom.h>
#include "../guicomponents/menu/MainMenu.h"
#include "../guicomponents/menu/SettingsMenu.h"

class MenuState : public phantom::GameState
{
public:
    MenuState();
    ~MenuState();

    void navigate(string to);

private:
    MainMenu *_mainMenu;
    SettingsMenu *_settingsMenu;
    //ServerMenu *_serverMenu;
    string _location;
};

#endif
