#ifndef MENUINPUTFIELD_H_
#define MENUINPUTFIELD_H_

#include <phantom.h>

class MenuInputField : public InputField
{
public:
    MenuInputField(float x, float y, float width, float height, phantom::Color color) : InputField(x, y, width, height, color) {}
    virtual void paint();
};

#endif