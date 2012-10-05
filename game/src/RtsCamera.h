#ifndef RTSCAMERA_H
#define	RTSCAMERA_H

#include <iostream>
#include <phantom.h>

using namespace phantom;
using namespace std;

class RtsCamera : public Composite {
public:
    RtsCamera();
    virtual void update(const float& elapsed);

private:
    float _scrollAreaSize;
    Camera* _phantomCamera;
    Input* _input;

    void draw(void);
};

#endif	/* RTSCAMERA_H */

