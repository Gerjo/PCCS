#ifndef MISSIONCOUNTER_H_
#define MISSIONCOUNTER_H_

#include <graphics/Graphics.h>

class MissionCounter {
public:
    inline void drawMe(phantom::Graphics *g, phantom::Vector3 *cursorPosition) {
        phantom::Box3 _bounds(1550.0f, 60.0f, 370.0f, 48.0f);

        string fontName = "fonts/arial.ttf";

        if(_bounds.contains(cursorPosition)) {
            string text = "Blaat";
            g->beginPath().setFillStyle(phantom::Colors::MIDNIGHTBLUE);
            for(unsigned i = 0; i < 5; ++i)
                g->text(_bounds.origin.x, _bounds.origin.y + (i * (_bounds.size.y)), static_cast<int>(_bounds.size.y / 2), fontName, text);
            g->stroke();
        }
        else {
            string text = "Missions";
            g->beginPath().setFillStyle(phantom::Colors::WHITE);
            g->text(_bounds.origin.x, _bounds.origin.y, static_cast<int>(_bounds.size.y / 2), fontName, text);
            g->stroke();
        }
    }
};

#endif