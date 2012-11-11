#include "Console.h"
#include "KeyboardListener.h"

#include <iostream>

Console* Console::INSTANCE = 0;

void Console::log(string log) {
    if(Console::INSTANCE != 0) {
        std::replace(log.begin(), log.end(), '\n', ' ');
        std::replace(log.begin(), log.end(), '\r', ' ');
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

    _width    = getPhantomGame()->getWorldSize().x;
    _height   = getPhantomGame()->getWorldSize().y / 2;
    _maxLines = 30;

    _keyboard = nullptr;

    setPosition(Vector3(
        0.0f,
        0.0f,
        0.0f)
        );

}

void Console::update(const Time& time) {
    Composite::update(time);

    Vector3 campos = getDriver()->getActiveCameras()->at(0)->getPosition();
    setPosition(campos);
    getGraphics().clear();

    if(!_enabled && getDriver()->getInput()->getKeyboardState()->isKeyDown('\\')) {
        _enabled = true;
        _keyboard = KeyboardListener::INSTANCE->lock(this);
    }

    if(_keyboard != nullptr) {
        for(char c : *_keyboard->changesUp()) {
            if(c == 27) {
                _keyboard = KeyboardListener::INSTANCE->unlock(this);
                _enabled = false;
            }
        }
    }

    if(_enabled) {
        draw();
    }
}

void Console::renderText(int offset, Color color) {
    Graphics& g = getGraphics().beginPath().setFillStyle(color);

    float lineheight = 32;
    float lineOffset = lineheight + lineheight;

    for(string& log : _logs) {
        g.text(0.0f, _height - lineOffset, 16, "fonts/waree.ttf", log);
        lineOffset += lineheight;
    }

    g.stroke();
}

void Console::renderInput() {
    if(_keyboard != nullptr) {
        for(char c : *_keyboard->changes()) {
            if(c == '\b') { // Action for backspace.
                if(_text.size() > 0) {
                    _text.erase(_text.end() - 1);
                }
            }
            else if(c == '\n' || c == '\r') {
                //TODO: Send current command located in _text.
                if(_text.substr(0, 4) == "\\pos" && _text.size() > 5) {
                    if(_text.substr(5, _text.size()) == "camera")
                        Console::log("Current position of the camera is: " + getDriver()->getActiveCameras()->at(0)->getPosition().toString());
                    else if(_text.substr(5, _text.size()) == "mouse")
                        Console::log("Current position of the mouse is: " + getDriver()->getInput()->getMouseState()->getMousePosition().toString());
                }
                _text.clear();
                _text.append(1, '\\');
            } else if(c < 28) { }
            else {
                _text.append(1, c);
            }
        }

        getGraphics().beginPath().text(0.0f, _height - 32, 16, "fonts/waree.ttf", _text).stroke();
    }
}

void Console::draw(void) {
    _doRedraw   = false;

    Graphics& g = getGraphics().clear().beginPath();
    g.setFillStyle(Color(0, 0, 0, 100));
    g.rect(0.0f, 0.0f, _width, _height);
    g.fill();

    renderText(+1, Colors::BLACK);
    renderText( 0, Colors::WHITE);
    renderInput();
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
