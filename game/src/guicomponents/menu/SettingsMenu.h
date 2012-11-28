#ifndef SETTINGSMENU_H_
#define SETTINGSMENU_H_

#include <phantom.h>
#include "MenuButton.h"
#include "MenuInputField.h"

class SettingsMenu : public phantom::Composite
{
public:
    SettingsMenu();
    ~SettingsMenu();

    void paint();
    void update(const phantom::PhantomTime& time);

private:
    enum MENUFIELDS {
        USERNAMETXT,
        RESOLUTIONTXT,
        SFXTXT,
        MUSICTXT
    };

    enum MENUBUTTONS {
        FULLSCREENBTN,
        BACKBTN
    };

    bool _repaint;
    vector<MenuButton*> _buttons;
    vector<MenuInputField*> _inputFields;

    void addActions();
    void loadSettings();
    void saveToFile();
    //vector<MenuLabel*> _labels;
};

#endif