#include "Console.h"

Console* Console::INSTANCE = 0;

void Console::log(string log) {
    if(Console::INSTANCE != 0) {
        Console::INSTANCE->addLog(log);
    } else {
        cout << log << endl;
    }
}

void Console::log(stringstream log) {
    Console::log(log.str());
}

Console::Console() : _doRedraw(true), _logCount(0) {
    setType("Console");
    Console::INSTANCE = this;

    _width    = 500;
    _height   = 150;
    _maxLines = 10;

    setPosition(Vector3(
            20.0f,
            getPhantomGame()->getViewPort().y - _height,
            0.0f)
    );

    addLog("Debug log initialized.");
}

void Console::update(const Time& time) {
    Composite::update(time);

    if(_doRedraw) {
        draw();
    }
}

void Console::renderText(int offset, Color color) {
    Graphics& g = getGraphics().beginPath().setFillStyle(color);

    float lineheight = 13;
    float lineOffset = lineheight;

    for(string& log : _logs) {
        g.text(static_cast<float>(offset), lineOffset + static_cast<float>(offset), 10, "fonts/waree.ttf", log);
        lineOffset += lineheight;
    }

    g.stroke();
}

void Console::draw(void) {
    _doRedraw   = false;
    Graphics& g = getGraphics().clear().beginPath();

    renderText(+1, Colors::BLACK);
    renderText( 0, Colors::WHITE);
}

void Console::addLog(string log) {
    stringstream formatted;
    formatted << "[" << _logCount << "] " << log;

    _logs.push_front(formatted.str());

    while(_logs.size() > _maxLines) {
        _logs.pop_back();
    }

    _logCount++;
    _doRedraw = true;
}
