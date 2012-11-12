#ifndef KEYBOARDLISTENER_H_
#define KEYBOARDLISTENER_H_

#include <core/Composite.h>
#include <core/Driver.h>
#include <thread>

class KeyboardListener {
public:
    static KeyboardListener *INSTANCE;

    KeyboardListener(phantom::Driver *driver, phantom::PhantomGame *game);
    ~KeyboardListener();

    void update();
    phantom::KeyboardState *lock(phantom::Composite* keycomp);
    phantom::KeyboardState *unlock(phantom::Composite* keycomp);
    bool isLocked() { return _locked; }

private:
    KeyboardListener(const KeyboardListener& copy){ }
    KeyboardListener* operator=(const KeyboardListener& copy){ return 0; }

    bool _locked;
    phantom::Composite *_key;
    phantom::Driver *_driver;
    phantom::PhantomGame *_game;
    std::thread *_thread;
};

#endif // !KEYBOARDLISTENER_H_
