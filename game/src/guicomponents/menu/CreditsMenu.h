#ifndef CREDITSMENU_H_
#define CREDITSMENU_H_

#include <phantom.h>
#include "MenuButton.h"

class CreditsMenu : public phantom::Composite
{
public:
    CreditsMenu();
    ~CreditsMenu();

    void paint();
    void update(const phantom::PhantomTime& time);
    
private:
    enum MENUBUTTONS {
        BACKBTN
    };

    std::vector<MenuButton*> _buttons;

    void addActions();
};
#endif

