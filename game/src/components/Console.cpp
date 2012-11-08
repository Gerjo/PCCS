#include "Console.h"
#include "KeyboardListener.h"

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

Console::Console() : _doRedraw(true), _logCount(0), _enabled(false) {
    setType("Console");
    Console::INSTANCE = this;

    _width    = 500;
    _height   = 325;
    _maxLines = 10;

    setPosition(Vector3(
        0.0f,
        0.0f,
        0.0f)
        );

}

void Console::update(const Time& time) {
    Composite::update(time);

    getGraphics().clear();

    if(!_enabled && getDriver()->getInput()->getKeyboardState()->isKeyDown('\\')) {
        _enabled = true;
        _hasKeyboardLock = KeyboardListener::INSTANCE->lock(this);
    }

    for(char c : *(getDriver()->getInput()->getKeyboardState()->changesUp())) {
        if(c == 27) {
            KeyboardListener::INSTANCE->unlock(this);
            _hasKeyboardLock = false;
            _enabled = false;
        }
    }

    if(_enabled) {
        draw();
    }
}

void Console::renderText(int offset, Color color) {
    Graphics& g = getGraphics().beginPath().setFillStyle(color);

    float lineheight = 20;
    float lineOffset = lineheight;

    for(string& log : _logs) {
        g.text(static_cast<float>(offset), lineOffset + static_cast<float>(offset), 16, "fonts/waree.ttf", log);
        lineOffset += lineheight;
    }

    g.stroke();
}

void Console::draw(void) {
    _doRedraw   = false;
    Graphics& g = getGraphics().clear();

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
