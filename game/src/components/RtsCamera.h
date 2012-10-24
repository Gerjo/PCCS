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
    Camera* getPhantomCamera();

private:
    void matchScreen(void);
    void draw(void);

    int _edgeSize;
    Camera* _phantomCamera;
    Input* _input;
    Box3 _edges[4];
    bool _hasMouse[4];
    Vector3 _normals[4];
};

#endif	/* RTSCAMERA_H */

