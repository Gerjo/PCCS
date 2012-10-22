#include "PreloaderText.h"

PreloaderText::PreloaderText() :
    _fontSize(12),
    _lineHeight(15),
    _lineCount(0),
    _maxLines(10),
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

    if(_texts.size() > _maxLines) {
        _texts.pop_front();
    }

    draw();
}

MessageState PreloaderText::handleMessage(AbstractMessage* message) {

    if(message->isType("loader-text")) {
        string payload = message->getPayload<string>();

        addText(payload);

        return CONSUMED;
    }

    return Composite::handleMessage(message);
}