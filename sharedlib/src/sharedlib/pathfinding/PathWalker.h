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

    PathWalker() : _target(nullptr), _speed(5), _previousPos(0, 0, 0), _firstRun(true) {
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

        return _route.back();
    }

private:
    float _speed;
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

        //cout << "target " << newTarget << endl;
        Composite* p = getParent();

        const Vector3& position = getParent()->getPosition();
        Vector3 direction = position.directionTo(newTarget);

        Pulse pulse;
        pulse.direction = direction;
        pulse.speed     = static_cast<char>(Services::settings()->pulse_dominant_speed);
        pulse.weight    = Services::settings()->pulse_dominant_weight;
        pulse.friction  = Services::settings()->pulse_dominant_friction;


        Message<Pulse> message("set-dominant-pulse", pulse);
        getParent()->handleMessage(&message);
    }
};

#endif	/* PATHWALKER_H */

