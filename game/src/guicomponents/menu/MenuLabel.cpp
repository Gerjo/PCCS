#include "MenuLabel.h"

MenuLabel::MenuLabel() : _text(""), _lastclick(0), _selected(false) {
    addComponent(new Clicktor());
}

MenuLabel::~MenuLabel() {
}

void MenuLabel::paint() {
    phantom::Color colorshade = _selected ? phantom::Color(0, 0, 0, 100) : phantom::Color(0, 0, 0, 50); 
    getGraphics().clear().beginPath().setFillStyle(colorshade).rect(0.0f, 0.0f, getBoundingBox().size.x, getBoundingBox().size.y).fill().
        setFillStyle(phantom::Colors::WHITE).text(0.0f, 0.0f, 16, "fonts/waree.ttf", _text).fill();
}

void MenuLabel::onClick(phantom::MouseState *mousestate) {
    onClickFunction();

    if(_lastclick > 0.001f) {
        onDoubleClickFunction();
    }
    _lastclick += 0.2f;
    _selected = _selected ? false : true;

    paint();
}

void MenuLabel::update(const phantom::PhantomTime& time) { 
    GameObject::update(time);

    if (_lastclick > 0.0f) { _lastclick -= time.getElapsed(); }
    else { _lastclick = 0.0f; }
}

string &MenuLabel::text() {
    return _text;
}

void MenuLabel::setText(std::string text) {
    _text = text;
}