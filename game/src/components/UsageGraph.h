#ifndef FPS_H
#define	FPS_H

#include <iostream>
#include <phantom.h>

using namespace phantom;

using std::cout;
using std::endl;

class UsageGraph : public Composite {
public:
    UsageGraph() : _frameCount(0), _interval(3) {
        _start = phantom::Util::getTime();
        _boundingBox.size.x = 300.0f;
        _boundingBox.size.y = 100.0f;

        _position.y = getPhantomGame()->getViewPort().y - _boundingBox.size.y - 20;
        _position.x = 20;
    }

    virtual void update(const PhantomTime& time) {
        Composite::update(time);

        if(++_frameCount != _interval) {
            return;
        }
        _frameCount = 0;

        int offset    = 0;
        int barwidth  = 5;

        double currentfps = 1 / (time.getTime() - _start) * _interval;

        _fps.push_back(currentfps);

        if(_fps.size() > _boundingBox.size.x / barwidth) {
            _fps.pop_front();
        }

        Graphics& g = getGraphics().clear().setFillStyle(Color(0, 0, 0, 20));

        g.rect(0, 0, _boundingBox.size.x, _boundingBox.size.y).stroke().beginPath().setFillStyle(Colors::WHITE);

        for(double fps : _fps) {
            float ypos   = static_cast<float>(fps);
            float yoffset = _boundingBox.size.y - ypos;
            g.rect(static_cast<float>(offset), yoffset, static_cast<float>(barwidth), ypos);

            offset += barwidth;
        }

        g.fill().stroke();

        g.beginPath().setFillStyle(Colors::BLACK);
        g.text(2, _boundingBox.size.y - 25, 15, "fonts/arial.ttf", "FPS: " + std::to_string(currentfps));
        g.fill();

        _start = time.getTime();
    }
private:
    double _start;
    deque<double> _fps;
    int _frameCount;
    int _interval;
};

#endif	/* FPS_H */
