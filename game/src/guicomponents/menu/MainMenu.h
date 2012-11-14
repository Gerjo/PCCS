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
    void update(const phantom::Time& time);

private:
    const unsigned int BUTTON_COUNT;

    bool _repaint;
    MenuButton _buttons[4];

    void addActions();
};
#endif
