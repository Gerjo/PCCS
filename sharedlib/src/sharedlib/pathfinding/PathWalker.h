#ifndef PATHWALKER_H
#define	PATHWALKER_H

#include <phantom.h>
using namespace phantom;

#include "Pathfinding.h"
#include "../services/Services.h"

// tmp:
#include <iostream>
using std::cout;
using std::endl;


//
// Note to self: we shall walk from front to back. So pop at front
// and push at the back.
//

class PathWalker : public Composite {
public:

    PathWalker() : _target(nullptr), _previousPos(0, 0, 0), _firstRun(true) {
        _xArrived = false;
        _yArrived = false;
    }

    void onParentChange(Composite* parent) {
        Composite::onParentChange(parent);
    }

    void setPath(Pathfinding::Route route) {
        // Let's use some of that C++11 goodness:
        _route  = std::move(route);
        _target = nullptr;
    }

    virtual void update(const PhantomTime& time) {
        if(_firstRun) {
            _previousPos = getParent()->getPosition();
            _firstRun = false;
        }

        // Load next target:
        if(_target == nullptr && !_route.empty()) {
            _target = &(_route.front());

            onTargetChange(_route.front());
        }

        // No targets at all:
        if(_target == nullptr) {
            return;
        }

        Vector3 position = getParent()->getPosition();

        Vector3 previousDistance = _previousPos.directionTo(*_target);
        Vector3 currentDistance  = position.directionTo(*_target);

        // Previous frame:
        const bool wasXpositive  = previousDistance.x >= 0;
        const bool wasYpositive  = previousDistance.y >= 0;

        // Current frame:
        const bool isXpositive   = currentDistance.x >= 0;
        const bool isYpositive   = currentDistance.y >= 0;

        if(isXpositive != wasXpositive) {
            _xArrived = true;
        }

        if(isYpositive != wasYpositive) {
            _yArrived = true;
        }

        float distance = position.distanceTo(*_target);

        //cout << std::fixed << distance << endl;

        if(_xArrived && _yArrived) {

            if(!hasNext()) {
                Pulse pulse;
                Message<Pulse> message("set-dominant-pulse", pulse);
                getParent()->handleMessage(&message);
            }


            gotoNextTarget();
        }

        adjustDirection();

        _previousPos = position;
        Composite::update(time);
    }

    virtual MessageState handleMessage(AbstractMessage* message) {
        if(message->isType("mover-set-path")) {
            setPath(message->getPayload<Pathfinding::Route>());

            return CONSUMED;
        }

        return Composite::handleMessage(message);
    }

    const Vector3& getTarget() {
        // Always return something, if only just our current position.
        if(_route.empty()) {
            return getParent()->getPosition();
        }

        return _route.front();
    }

    Vector3 getEasingTarget(void) {
        const Vector3 position = getParent()->getPosition();
        const Box3 fieldOfView(position, Vector3(100.0f, 100.0f, 0.0f));
        Vector3 result;

        // First line, my post to first way point.
        Line2 test(position, _route.front());
        size_t i = 1;

        //getParent()->getGraphics().beginPath().setFillStyle(Colors::GREEN)
        //        .rect(0, 0, fieldOfView.size.x, fieldOfView.size.y, false).fill();


        do {
            Vector3 intersect = fieldOfView.intersection(test);

            getParent()->getGraphics().beginPath().line(test.a - position, test.b - position);

            if(intersect.isFinite()) {
                result = intersect;
                getParent()->getGraphics().setFillStyle(Colors::GREEN).fill();
            } else {
                getParent()->getGraphics().setFillStyle(Colors::RED).fill();
            }

            // My code logic smells, so this is required.
            if(i >= _route.size()) {
                break;
            }

            test.a = test.b;
            test.b = _route.at(i);

        } while(i++ < _route.size());

        getParent()->getGraphics().beginPath().line(Vector3(), result - position).setFillStyle(Colors::MIDNIGHTBLUE).fill();

        return result;
    }

private:
    Pathfinding::Route _route;
    Vector3* _target;
    Vector3 _previousPos;
    bool _firstRun;
    bool _xArrived;
    bool _yArrived;

    void gotoNextTarget() {
        if(!_route.empty()) {
            _route.pop_front();
        }

        if(!_route.empty()) {
            _target = & (_route.front());
            onTargetChange(_route.front());
        } else {
            _target = nullptr;
        }
    }

    bool hasNext() {
        return _route.size() > 1;
    }

    void onTargetChange(const Vector3& newTarget) {
        _xArrived = false;
        _yArrived = false;

        return;

        /*
        const Vector3& position = getParent()->getPosition();
        Vector3 direction = position.directionTo(newTarget);

        Pulse pulse;
        pulse.direction = direction;
        pulse.speed     = static_cast<char>(Services::settings()->pulse_dominant_speed);
        pulse.weight    = Services::settings()->pulse_dominant_weight;
        pulse.friction  = Services::settings()->pulse_dominant_friction;


        Message<Pulse> message("set-dominant-pulse", pulse);
        getParent()->handleMessage(&message);*/
    }

    void adjustDirection(void) {
        if(_target) {
            const Vector3& position = getParent()->getPosition();
            Vector3 target = getEasingTarget();//_target; //

            //Vector3 idirection = getParent()->getComponentByType<InertiaMover>()->getDirection();
            Vector3 direction  = position.directionTo(target);//idirection.directionTo(*_target);
            direction *= 0.15;

            Message<Vector3> message("add-dominant-direction", direction);
            getParent()->handleMessage(&message);

            // test call
            getEasingTarget();
        }
    }
};

#endif	/* PATHWALKER_H */

