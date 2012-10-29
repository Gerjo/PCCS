#ifndef CLICKABLECOMPOSITE_H_
#define CLICKABLECOMPOSITE_H_

#include <core/Composite.h>
#include <utils/Time.h>
#include <physics/Vector3.h>
#include <input/MouseState.h>

class ClickableComposite : public phantom::Composite
{
public:
    ClickableComposite();
    ~ClickableComposite();

    virtual void clicked(phantom::MouseState& mouseState) = 0;
    virtual void update(const phantom::Time& time);
};

#endif // !CLICKABLECOMPOSITE_H_
