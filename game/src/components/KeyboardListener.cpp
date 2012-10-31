#include "KeyboardListener.h"

KeyboardListener::KeyboardListener() : _locked(false) { }

void KeyboardListener::update(const phantom::Time& time) {
    if(!_locked) {
        // Allows us to quick exit the game.
        if(getDriver()->getInput()->getKeyboardState()->isKeyDown(27)) {
            getPhantomGame()->exit(0);
        }
    }
}

bool KeyboardListener::lock(Composite* keycomp) {
    if(_locked) return false;
    else {
        _locked = true;
        _key = keycomp;
        return true;
    }
}

void KeyboardListener::unlock(Composite* keycomp) {
    if(keycomp == _key)
        _locked = false;
}