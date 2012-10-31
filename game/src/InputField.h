#ifndef INPUTFIELD_H_
#define INPUTFIELD_H_

#include <string>

#include <input/MouseState.h>
#include <graphics/Color.h>
#include <utils/Time.h>
#include <sharedlib/ClickableEntity.h>

class KeyboardListener;

class InputField : public ClickableEntity {
public:
    InputField(float x, float y, float width, float height, phantom::Color color);
    ~InputField();

    void clicked(const phantom::MouseState& mouseState);
    void unclicked(const phantom::MouseState& mouseState);
    void update(const phantom::Time& time);

    void keyboard(KeyboardListener *keyboardListener) { _keyboardListener = keyboardListener; }

    std::string& text();
    void text(std::string value);

private:
    bool _hasFocus;
    phantom::Color _color;
    std::string _text;
    KeyboardListener *_keyboardListener;
};

#endif