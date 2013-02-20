#ifndef MENUBUTTON_H_
#define MENUBUTTON_H_

#include <phantom.h>
#include <string>

class MenuButton : public phantom::Button
{
public:
    MenuButton(float x, float y, float width = 807.0f, float height = 136.0f);
    ~MenuButton();

    void paint();
};

#endif // MENUBUTTON_H_
