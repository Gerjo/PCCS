#ifndef MENULABEL_H_
#define MENULABEL_H_

#include <functional>

#include <input/MouseState.h>
#include "../../components/Clicktor.h"
#include <sharedlib/gameobjects/GameObject.h>

class MenuLabel : public GameObject {
public:
    MenuLabel();
    ~MenuLabel();

    void paint();
    void update(const phantom::Time& time);
    void onClick(phantom::MouseState *mousestate);

    string &text();
    void setText(std::string text);

    std::function<void()> onClickFunction;
    std::function<void()> onDoubleClickFunction;
private:
    std::string _text;
    float _lastclick;
    bool _selected;
};


#endif