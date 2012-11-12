#ifndef CLICKTOR_H_
#define CLICKTOR_H_

#include <core/Composite.h>
#include <core/Camera.h>
#include <input/MouseState.h>

class Clicktor : public phantom::Composite
{
public:
    virtual void setCamera(phantom::Camera *camera);
    virtual void update(const phantom::Time& time);
private:
    phantom::Camera *_camera;
};

#endif // !CLICKTOR_H_