#include "HeavyEnemy.h"
#include <core/Camera.h>

HeavyEnemy::HeavyEnemy(Data enemyinfo) : LightEnemy(enemyinfo), _time(0, 0, 0), _requiresRedraw(true) {
    addComponent(new HealthBar());
    _width = enemyinfo("width");
    _height = enemyinfo("height");
    _images = enemyinfo("graphics").toVector<Data>();
}

void HeavyEnemy::update(const phantom::PhantomTime &time) {
    LightEnemy::update(time);
    _time = time;
    paint();
}

void HeavyEnemy::paint() {
    // I'm pretty sure the 2nd one is hacky...
    if(!_requiresRedraw || !Box3(getPhantomGame()->getDriver()->getActiveCameras()->at(0)->getPosition(), getPhantomGame()->getViewPort()).intersect(Box3(getPosition(), getBoundingBox().size)))
        return;

    _requiresRedraw = false;

    stringstream rotationNumber;
    ImageDirections::to8Directions(rotationNumber, phantom::maths::directionToRotation(&_direction));

    getGraphics().clear().beginPath();
    for(Data value : _images) {
        Color color = Colors::WHITE;
        float posx = 0.0f;
        float posy = 0.0f;

        if(value.hasKey("offsetx")) {
            posx = value("offsetx");
        }

        if(value.hasKey("offsety")) {
            posy = value("offsety");
        }

        if(value.hasKey("color")) {
            Data valuecolor = value("color");
            color = Color(static_cast<int>(valuecolor("r")), static_cast<int>(valuecolor("g")), static_cast<int>(valuecolor("b")), static_cast<int>(valuecolor("a")));
        }
        getGraphics().setFillStyle(color);

        string imagelocation = value("location");
        string::size_type loc = imagelocation.find("(img)");
        if(value.hasKey("directed") && static_cast<int>(value("directed")) == 1) {
            imagelocation.replace(loc, 5, rotationNumber.str());
        }
        else if(value.hasKey("nextcount") && static_cast<int>(value("nextcount")) != 0) {
            stringstream s;
            unsigned int time = static_cast<int>((this->_time.getTotalGameTime() * 1000.0f) / 60.0f);
            unsigned int count = static_cast<int>(value("nextcount"));
            s << (time % count) + 1;
            imagelocation.replace(loc, 5, s.str());
            _requiresRedraw = true;
        }

        getGraphics().image(imagelocation, posx, posy, _width, _height).fill();
    }
}

void HeavyEnemy::repaint() {
    _requiresRedraw = true;
}

void HeavyEnemy::move(const Vector3 &location) {
    LightEnemy::move(location);
    paint();
}

void HeavyEnemy::fromData(Data& data) {
    LightEnemy::fromData(data);
    repaint();
}
