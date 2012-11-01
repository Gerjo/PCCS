#ifndef RTSCAMERA_H
#define	RTSCAMERA_H

#include <iostream>
#include <phantom.h>

using namespace phantom;
using namespace std;

class ScrollBehaviour : public Composite {
public:
    ScrollBehaviour();
    virtual void update(const Time& time);

    void setScrollableObject(Composite *scrollableObject) {
        _scrollableObject = scrollableObject;
    }

private:
    void matchScreen(void);
    void draw(void);

    Composite *_scrollableObject;
    int _edgeSize;
    Input* _input;
    Box3 _edges[4];
    bool _hasMouse[4];
    Vector3 _normals[4];
};

#endif	/* RTSCAMERA_H */

