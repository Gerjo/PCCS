#ifndef TIMER_H
#define	TIMER_H

#include <phantom.h>

using phantom::Time;

class Timer {
public:
    Timer(double delay) : _delay(delay), _startTime(phantom::Util::getTime()) {

    }

    // Slightly more efficient overload. The update loop of our game
    // supplies a Time object.
    bool hasExpired(const Time& time) {
        if(time.getTotalGameTime() - _startTime > _delay) {
            return true;
        }

        return false;
    }

    bool hasExpired() {
        double now = phantom::Util::getTime();

        if(now - _startTime > _delay) {
            return true;
        }

        return false;
    }

    void restart() {
        _startTime = phantom::Util::getTime();
    }

private:
    double _startTime;
    double _delay;
};

#endif	/* TIMER_H */

