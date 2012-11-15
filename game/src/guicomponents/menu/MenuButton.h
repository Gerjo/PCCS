#ifndef MENUBUTTON_H_
#define MENUBUTTON_H_

#include <phantom.h>
#include <string>
#include <sharedlib/gameobjects/GameObject.h>
#include "../../components/Clicktor.h"

class MenuButton : public GameObject
{
public:
    MenuButton();
    ~MenuButton();

    void onClick(MouseState *mousestate);

    void setText(std::string text);
    void paint();

    std::function<void()> onClickFunction;

private:
    std::string _text;
    bool _isBusy;
};

#endif // MENUBUTTON_H_
