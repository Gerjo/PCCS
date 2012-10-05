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
    void matchScreen(void);
    void draw(void);

    int _edgeSize;
    Camera* _phantomCamera;
    Input* _input;

    Box3 _edges[4];

    Box3 _top;
    Box3 _bottom;
    Box3 _left;
    Box3 _right;
};

#endif	/* RTSCAMERA_H */

