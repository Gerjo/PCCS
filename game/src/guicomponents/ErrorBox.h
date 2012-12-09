#ifndef ERRORBOX_H_
#define ERRORBOX_H_

#include <phantom.h>
#include <vector>
#include <string>
#include "menu/MenuButton.h"

using std::string;

class ErrorBox : public phantom::Composite {
public:
    ErrorBox(string message);
    ~ErrorBox();
    virtual void update(const phantom::PhantomTime &time);
    void paint();

private:
    MenuButton *_okButton;
    string _message;
    bool _repaint;
};

#endif