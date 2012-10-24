#include "PreloaderText.h"

PreloaderText::PreloaderText() :
    _fontSize(10),
    _lineHeight(12),
    _lineCount(0),
    _maxLines(15),
    _font("fonts/DejaVuSansMono-Bold.ttf")
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


    string str = ss.str();

    if(str.length() > 100) {
        str.resize(100);
        str += " [...]";
    }

    _texts.push_back(str);

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