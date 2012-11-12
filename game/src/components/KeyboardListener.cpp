#include "KeyboardListener.h"
#include "../GameException.h"

KeyboardListener* KeyboardListener::INSTANCE = 0;

using namespace phantom;

KeyboardListener::KeyboardListener(Driver *driver, PhantomGame *game) : _locked(false) {
    if(INSTANCE == 0) {
        _driver = driver;
        _game = game;
        INSTANCE = this;
    }
    else
        throw GameException("Keyboard not found. Press F1 to continue.");
}

KeyboardListener::~KeyboardListener() {
}

void KeyboardListener::update() {
    if(!KeyboardListener::INSTANCE->isLocked()) {
        // Allows us to quick exit the game.        
        if(_driver->getInput()->getKeyboardState()->isKeyDown(27)) {
            _game->exit(0);
            return;
        }
    }
}

KeyboardState *KeyboardListener::lock(Composite* keycomp) {
    if(_locked) return nullptr;
    else {
        _locked = true;
        _key = keycomp;
        return _driver->getInput()->getKeyboardState();
    }
}

KeyboardState *KeyboardListener::unlock(Composite* keycomp) {
    if(keycomp == _key) {
        _locked = false;
    }
    return nullptr;
}