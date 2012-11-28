#pragma once

#include <phantom.h>
#include "MenuButton.h"
#include "MenuInputField.h"
#include "MenuLabel.h"
#include "../../networking/Dedicated.h"
#include <sharedlib/models/DedicatedModel.h>

class ServerBrowser : public phantom::Composite
{
public:
    ServerBrowser();
    ~ServerBrowser();

    void servers(vector<DedicatedModel> servers); 
    void paint();
    void update(const phantom::PhantomTime& time);

    DedicatedModel selectedServer;
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

