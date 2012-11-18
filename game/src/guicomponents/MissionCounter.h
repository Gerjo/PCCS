#ifndef MISSIONCOUNTER_H_
#define MISSIONCOUNTER_H_

#include <core/Composite.h>
#include <graphics/Graphics.h>

class MissionCounter : public phantom::Composite {
public:
    std::vector<std::string> missions;
    bool visible;

    virtual void update(const phantom::Time& time) {
        phantom::Vector3 cursorPosition = getDriver()->getInput()->getMouseState()->getPosition();

        phantom::Box3 _bounds(1550.0f, 60.0f, 370.0f, 48.0f);

        string fontName = "fonts/arial.ttf";

        getGraphics().clear();

        if(_bounds.contains(cursorPosition)) {
            getGraphics().beginPath().setFillStyle(phantom::Colors::MIDNIGHTBLUE);
            int count = 0;
            for(std::string mission : missions) {
                getGraphics().text(_bounds.origin.x, _bounds.origin.y + (count * (_bounds.size.y / 3 * 2)), static_cast<int>(_bounds.size.y / 3), fontName, mission);
                ++count;
            }
            getGraphics().stroke();
        }
        else {
            getGraphics().beginPath().setFillStyle(phantom::Colors::WHITE);
            stringstream s;
            s << "Missions: " << missions.size();
            getGraphics().text(_bounds.origin.x, _bounds.origin.y, static_cast<int>(_bounds.size.y / 2), fontName, s.str());
            getGraphics().stroke();
        }
    }
};

#endif