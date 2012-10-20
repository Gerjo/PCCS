#ifndef NEWCLASS_H
#define	NEWCLASS_H

#include <phantom.h>
#include <string>
#include <deque>

using namespace phantom;

class PreloaderText : public Composite {
public:
    PreloaderText();
    void addText(string text);

private:
    deque<string> _texts;
    unsigned _fontSize;
    float _lineHeight;
    int _lineCount;
    string _font;
    int _maxLines;

    void draw(void);
};

#endif	/* NEWCLASS_H */
