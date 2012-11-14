#ifndef ROCKETS_BITCHES
#define ROCKETS_BITCHES

#include "WeaponBehaviour.h"

class LIBEXPORT RocketLauncher : public WeaponBehaviour{
public:
    RocketLauncher();
    virtual void render(phantom::Graphics* g);
};

#endif /* ROCKETS_BITCHES */