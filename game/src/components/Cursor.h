#ifndef CURSOR_H
#define	CURSOR_H

#include <phantom.h>
#include <string>

using namespace std;
using namespace phantom;

class Cursor : public Entity {
    public:
        Cursor();
        void draw(void);
        void update(const float& elapsed);

        void setTooltip(string tooltip);
    private:
        string _tooltip;
        bool _doRedraw;
};

#endif	/* CURSOR_H */

