#include "MainMenu.h"


MainMenu::MainMenu() : _repaint(false) {
    paint();
}


MainMenu::~MainMenu() {
}

void MainMenu::paint() {
    phantom::Graphics &g = getGraphics();

    g.clear();
}

void MainMenu::update(const phantom::Time& time) {
    Composite::update(time);
    if(_repaint)
        paint();
}
