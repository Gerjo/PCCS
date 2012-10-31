#ifndef KEYBOARDLISTENER_H_
#define KEYBOARDLISTENER_H_

#include <core/Composite.h>
#include <core/Driver.h>

class KeyboardListener : public phantom::Composite {
public:
    KeyboardListener() : _locked(false) { }

    void update(const phantom::Time& time) {
        if(!_locked) {
            // Allows us to quick exit the game.
            if(getDriver()->getInput()->getKeyboardState()->isKeyDown(27)) {
                getPhantomGame()->exit(0);
            }
        }
    }

    void lock()   { _locked = true;  };
    void unlock() { _locked = false; };

private:
    bool _locked;
};

#endif // !KEYBOARDLISTENER_H_
