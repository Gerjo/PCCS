#ifndef MENUBUTTON_H_
#define MENUBUTTON_H_

#include <core/Composite.h>
#include <string>
#include "../../components/Clicktor.h"

class MenuButton : public phantom::Composite
{
public:
    MenuButton();
    ~MenuButton();

    void setText(std::string text);
    void paint();

private:
    std::string _text;
};

#endif // MENUBUTTON_H_
