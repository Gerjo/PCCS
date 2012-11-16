#ifndef MENUINPUTFIELD_H_
#define MENUINPUTFIELD_H_

#include "../InputField.h"

class MenuInputField : public InputField
{
public:
    MenuInputField(float x, float y, float width, float height, phantom::Color color) : InputField(nullptr, x, y, width, height, color) {}
    virtual void paint();
};

#endif