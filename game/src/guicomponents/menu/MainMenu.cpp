#include "MainMenu.h"

MainMenu::MainMenu() : _repaint(false), BUTTON_COUNT(4) {
    paint();

    _buttons[0].setText("Join");
    _buttons[1].setText("Settings");
    _buttons[2].setText("Credits");
    _buttons[3].setText("Exit");
}


MainMenu::~MainMenu() {
}

void MainMenu::paint() {
    phantom::Graphics &g = getGraphics();

    g.clear().beginPath().setFillStyle(phantom::Colors::WHITE).
        image("images/menu/bg.png", 0.0f, 0.0f, getPhantomGame()->getWorldSize().x, getPhantomGame()->getWorldSize().y).
        stroke();

    for(unsigned int i = 0; i < BUTTON_COUNT; ++i)
        _buttons[i].paint();
}

void MainMenu::update(const phantom::Time& time) {
    Composite::update(time);
    if(_repaint)
        paint();
}

void MainMenu::addActions() {
    std::function<void()> join, settings, credits, exit;

    join = [] () { /* open server browser */ };
    settings = [] () { /* open settings dialog */ };
    credits = [] () { /* open credits dialog */ };
    exit = [this] () { getPhantomGame()->exit(0); };
}