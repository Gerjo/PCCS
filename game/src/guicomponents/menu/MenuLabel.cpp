#include "MenuLabel.h"

MenuLabel::MenuLabel() : _text(""), _clickcount(0) {
}

MenuLabel::~MenuLabel() {
}

void MenuLabel::paint() {
    getGraphics().clear().beginPath().setFillStyle(phantom::Color(0, 0, 0, 100)).rect(0.0f, 0.0f, getBoundingBox().size.x, getBoundingBox().size.y).fill().
        setFillStyle(phantom::Colors::WHITE).text(0.0f, 0.0f, 16, "fonts/waree.ttf", _text).fill();
}

void MenuLabel::onClick(phantom::MouseState *mousestate) {
}

string &MenuLabel::text() {
    return _text;
}

void MenuLabel::setText(std::string text) {
    _text = text;
}