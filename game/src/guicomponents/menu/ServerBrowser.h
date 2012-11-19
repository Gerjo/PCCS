#pragma once

#include <phantom.h>
#include "MenuButton.h"
#include "MenuInputField.h"
#include "MenuLabel.h"

class ServerBrowser : public phantom::Composite
{
public:
    ServerBrowser();
    ~ServerBrowser();

    void paint();
    void update(const phantom::Time& time);

private:
    enum MENUBUTTONS {
        BTNREFRESH,
        BTNJOIN,
        BTNBACK
    };

    bool _repaint;
    vector<MenuButton *> _buttons;
    vector<MenuLabel *> _labels;

    void addActions();
};

