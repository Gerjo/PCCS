#ifndef ACTIONBAR_H_
#define ACTIONBAR_H_

#include <graphics/Graphics.h>

class ActionBar {
public:
    void drawMe(phantom::Graphics *g) {
        g->beginPath().setFillStyle(phantom::Colors::WHITE).image("images/hud menu/Menu BG.png", 579.5f, 917.0f, 761.0f, 163.0f).stroke();
    }
};

#endif