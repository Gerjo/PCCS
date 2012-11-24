#ifndef CURSOR_H
#define	CURSOR_H

#include <phantom.h>
#include <string>

using namespace std;
using namespace phantom;

class Cursor : public Entity {

public:
    enum CURSORIMG {
        CURNORMAL,
        CURATTACK
    };

    CURSORIMG currentCursor;

    Cursor();
    void draw(void);
    void update(const Time& time);
    void redraw();
    void setTooltip(string tooltip);

private:
    int _rotation;
    string _tooltip;
    bool _doRedraw;
};

#endif	/* CURSOR_H */

