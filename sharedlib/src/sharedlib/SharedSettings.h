#ifndef SHAREDSETTINGS_H
#define SHAREDSETTINGS_H

#include <string>
#include "CompileConfig.h"

class LIBEXPORT SharedSettings {
public:
    static void load(void);
    static double PING_INTERVAL();

    static double PING_INTERVALMASTER();

    static std::string MASTER_HOST();
    static int MASTER_PORT();

    static float BSP_WIDTH();
    static float BSP_HEIGHT();
    static float BSP_SMALLESTSIZE();
    static unsigned BSP_MAXCOLLISIONSPERSPACE();
};


#endif /* SHAREDSETTINGS_H */