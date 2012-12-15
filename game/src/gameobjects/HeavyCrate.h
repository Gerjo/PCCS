#ifndef HEAVYCRATE_H
#define HEAVYCRATE_H

#include <common/CompileConfig.h>
#include <sharedlib/gameobjects/LightCrate.h>

class LIBEXPORT HeavyCrate: public LightCrate{
public:
    HeavyCrate();
    void paint();
};


#endif /* HEAVYCRATE_H */