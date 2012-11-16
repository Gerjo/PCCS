#pragma once

#include <phantom.h>
#include "MenuButton.h"
#include "MenuInputField.h"

class ServerBrowser : public phantom::Composite
{
public:
    ServerBrowser();
    ~ServerBrowser();

    void paint();
    void update(const phantom::Time& time);

private:
    enum MENUITEMS {
    };

    bool _repaint;
    vector<MenuButton *> _buttons;

    void addActions();
};

