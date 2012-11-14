#ifndef MENU_H_
#define MENU_H_

#include <phantom.h>
#include "../guicomponents/menu/MainMenu.h"

class MenuState : public phantom::GameState
{
public:
    MenuState();
    ~MenuState();

    void navigate(string to);

private:
    MainMenu *_mainMenu;
    //ConfigurationMenu *_configurationMenu;
    //ServerMenu *_serverMenu;
    string _location;
};

#endif
