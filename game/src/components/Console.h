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

    virtual void update(const float& elapsed);
    void addLog(string log);

private:
    static Console* INSTANCE;
    deque<string> _logs;
    bool _doRedraw;

    void draw(void);
    void renderText(int offset, Color color);

    float _width;
    float _height;
    int _maxLines;
    int _logCount;
};

#endif	/* CONSOLE_H */

