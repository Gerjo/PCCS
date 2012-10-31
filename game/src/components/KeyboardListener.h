#ifndef KEYBOARDLISTENER_H_
#define KEYBOARDLISTENER_H_

#include <core/Composite.h>
#include <core/Driver.h>

class KeyboardListener : public phantom::Composite {
public:
    KeyboardListener();
    void update(const phantom::Time& time);
    bool lock(Composite* keycomp);
    void unlock(Composite* keycomp);
private:
    bool _locked;
    Composite *_key;
};

#endif // !KEYBOARDLISTENER_H_
