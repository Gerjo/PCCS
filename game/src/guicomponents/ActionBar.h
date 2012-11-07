#ifndef ACTIONBAR_H_
#define ACTIONBAR_H_

#include <graphics/Graphics.h>

class ActionBar {
public:
    inline void drawMe(phantom::Graphics *g) {
        float loc[] = { 579.5f, 917.0f };

        g->beginPath().setFillStyle(phantom::Colors::WHITE)
            .image("images/hud menu/menu bg.png", loc[0], loc[1], 761.0f, 163.0f)
            .image("images/hud menu/menu 1.png", loc[0] + 10.0f, loc[1] + 10.0f, 209.0f, 68.0f)
            .image("images/hud menu/menu 2.png", loc[0] + 225.0f, loc[1] + 10.0f, 209.0f, 68.0f)
            .image("images/hud menu/menu 3.png", loc[0] + 10.0f, loc[1] + 85.0f, 209.0f, 68.0f)
            .image("images/hud menu/menu 4.png", loc[0] + 225.0f, loc[1] + 85.0f, 209.0f, 68.0f)
            .image("images/hud menu/menu inventory.png", loc[0] + 450.0f, loc[1] + 10.0f, 296.0f, 144.0f)
            .stroke();
    }
};

#endif