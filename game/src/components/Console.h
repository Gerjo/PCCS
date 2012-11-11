#ifndef CONSOLE_H
#define	CONSOLE_H

#include <phantom.h>
#include <deque>
#include <sstream>

using namespace phantom;
using namespace std;

class Console : public Composite {
public:
    Console();
    static void log(string log);
    static void log(stringstream log);

    template<class mType>
    static void log(Message<mType> log){
        Console::log(log.getType());
        Console::log(log.getData());
    }

    virtual void update(const Time& time);
    void addLog(string log);

private:
    static Console* INSTANCE;
    deque<string> _logs;
    bool _doRedraw;
    bool _enabled;
    KeyboardState *_keyboard;

    void draw(void);
    void renderText(int offset, Color color);
    void renderInput();

    float _width;
    float _height;
    unsigned int _maxLines;
    int _logCount;
    string _text;
};

#endif	/* CONSOLE_H */

