#ifndef HEAVYCRATE_H
#define HEAVYCRATE_H

#include <common/CompileConfig.h>
#include <sharedlib/gameobjects/Crate.h>

class LIBEXPORT HeavyCrate: public Crate{
public:
    HeavyCrate();

    void paint();
};


#endif /* HEAVYCRATE_H */