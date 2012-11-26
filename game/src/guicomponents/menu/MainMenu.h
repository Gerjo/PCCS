#ifndef MAINMENU_H_
#define MAINMENU_H_

#include <phantom.h>
#include "MenuButton.h"

class MainMenu : public phantom::Composite
{
public:
    MainMenu();
    ~MainMenu();
    
    void paint();
    void update(const phantom::PhantomTime& time);

private:
    enum MENUITEMS {
        JOIN,
        SETTINGS,
        CREDITS,
        EXIT
    };

    bool _repaint;
    vector<MenuButton *> _buttons;

    void addActions();
};
#endif
