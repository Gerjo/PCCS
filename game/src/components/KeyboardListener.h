#ifndef KEYBOARDLISTENER_H_
#define KEYBOARDLISTENER_H_

#include <core/Composite.h>
#include <core/Driver.h>

class KeyboardListener : public phantom::Composite {

    void update(const phantom::Time& time) { 
        // Allows us to quick exit the game.
        if(getDriver()->getInput()->getKeyboardState()->isKeyDown(27)) {
            getPhantomGame()->exit(0);
        }
    }
};

#endif // !KEYBOARDLISTENER_H_
