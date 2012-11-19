#ifndef MENULABEL_H_
#define MENULABEL_H_

#include <functional>

#include <core/Composite.h>
#include <input/MouseState.h>
#include "../../components/Clicktor.h"

class MenuLabel : public phantom::Composite {
public:
    MenuLabel();
    ~MenuLabel();

    void paint();
    void onClick(phantom::MouseState *mousestate);

    string &text();
    void setText(std::string text);

    std::function<void()> onClickFunction;
    std::function<void()> onDoubleClickFunction;
private:
    std::string _text;
    int _clickcount;
};


#endif