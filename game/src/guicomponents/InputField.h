#ifndef INPUTFIELD_H_
#define INPUTFIELD_H_

#include <string>

#include <input/MouseState.h>
#include <graphics/Color.h>
#include <utils/Time.h>
#include <sharedlib/gameobjects/GameObject.h>
#include <input/KeyboardListener.h>

class InputField : public GameObject {
public:
    InputField(phantom::Camera *camera, float x, float y, float width, float height, phantom::Color color);
    ~InputField();

    virtual void onClick(MouseState *mousestate);
    virtual void onUnClicked(MouseState *mousestate);
    virtual void paint();
    virtual void update(const phantom::Time& time);

    void keyboard(KeyboardListener *keyboardListener) { _keyboardListener = keyboardListener; }

    std::string& text();
    void text(std::string value);

private:
    bool                _hasFocus;
    phantom::Color      _color;
    std::string         _text;
    KeyboardListener    *_keyboardListener;
};

#endif