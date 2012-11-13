#ifndef MISSIONCOUNTER_H_
#define MISSIONCOUNTER_H_

#include <graphics/Graphics.h>

class MissionCounter {
public:
    std::vector<std::string> missions;

    inline void drawMe(phantom::Graphics *g, phantom::Vector3 *cursorPosition) {
        phantom::Box3 _bounds(1550.0f, 60.0f, 370.0f, 48.0f);

        string fontName = "fonts/arial.ttf";

        if(_bounds.contains(cursorPosition)) {
            g->beginPath().setFillStyle(phantom::Colors::MIDNIGHTBLUE);
            int count = 0;
            for(std::string mission : missions) {
                g->text(_bounds.origin.x, _bounds.origin.y + (count * (_bounds.size.y / 3 * 2)), static_cast<int>(_bounds.size.y / 3), fontName, mission);
                ++count;
            }
            g->stroke();
        }
        else {
            g->beginPath().setFillStyle(phantom::Colors::WHITE);
            stringstream s;
            s << "Missions: " << missions.size();
            g->text(_bounds.origin.x, _bounds.origin.y, static_cast<int>(_bounds.size.y / 2), fontName, s.str());
            g->stroke();
        }
    }
};

#endif