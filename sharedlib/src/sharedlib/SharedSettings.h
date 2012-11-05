#ifndef SHAREDSETTINGS_H
#define SHAREDSETTINGS_H

#include "CompileConfig.h"

class LIBEXPORT SharedSettings {
public:
    static void load(void);
    static double PING_INTERVAL();

    static unsigned int UNIQUE_ID();
    static float BSP_WIDTH();
    static float BSP_HEIGHT();
    static float BSP_SMALLESTSIZE();
    static unsigned BSP_MAXCOLLISIONSPERSPACE();
};


#endif /* SHAREDSETTINGS_H */