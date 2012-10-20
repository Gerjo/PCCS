#include "PreloaderText.h"

PreloaderText::PreloaderText() :
    _fontSize(12),
    _lineHeight(15),
    _lineCount(0),
    _font("fonts/waree.ttf")
{
    _position.x = 250;
    _position.y = 340;
}

void PreloaderText::draw() {
    Graphics& g = getGraphics()
            .clear()
            .beginPath()
            .setFillStyle(Colors::WHITE)
            ;

    float i = 0.0f;
    for(string str : _texts) {
        g.text(0.0f, ++i * _lineHeight, _fontSize, &_font, &str);
    }

    g.fill();
}

void PreloaderText::addText(string text) {
    stringstream ss;

    ss << "[" << ++_lineCount << "] " << text;

    _texts.push_back(ss.str());
    draw();
}