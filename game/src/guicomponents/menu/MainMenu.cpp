#include "MainMenu.h"
#include "../../Game.h"
#include "../../gamestates/ClientWorld.h"
#include "../../gamestates/MenuState.h"
#include "../../gamestates/Loader.h"

MainMenu::MainMenu() : _repaint(false) {
    for(unsigned int i = 0; i < 4; ++i) {
        MenuButton *b = new MenuButton();
        b->setPosition(phantom::Vector3(556.5f, 340.0f + (i * 140.0f)));
        _buttons.push_back(b);
        addComponent(b);
    }
    
    _buttons[JOIN]->setText("Join");
    _buttons[SETTINGS]->setText("Settings");
    _buttons[CREDITS]->setText("Credits");
    _buttons[EXIT]->setText("Exit");

    addActions();

    paint();
}

MainMenu::~MainMenu() {
}

void MainMenu::paint() {
    phantom::Graphics &g = getGraphics();

    g.clear().clear().beginPath().setFillStyle(phantom::Colors::WHITE).
        image("images/menu/bg.png", 0.0f, 0.0f, getPhantomGame()->getWorldSize().x, getPhantomGame()->getWorldSize().y).
        stroke();

    for(MenuButton *button : _buttons)
        button->paint();
}

void MainMenu::update(const phantom::Time& time) {
    if(_repaint)
        paint();
    Composite::update(time);
}

void MainMenu::addActions() {
    std::function<void()> join, settings, credits, exit;

    join = [this] () { getGame<Game*>()->launchLoader(); };
    settings = [this] () { static_cast<MenuState*>(getParent())->navigate("settings"); };
    credits = [this] () { static_cast<MenuState*>(getParent())->navigate("credits"); };
    exit = [this] () { getPhantomGame()->exit(0); };

    _buttons[JOIN]->onClickFunction = join;
    _buttons[SETTINGS]->onClickFunction = settings;
    _buttons[CREDITS]->onClickFunction = credits;
    _buttons[EXIT]->onClickFunction = exit;
}