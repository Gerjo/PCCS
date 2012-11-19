#ifndef VPOINT_H
#define VPOINT_H

#include <CompileConfig.h>

namespace PGC{
    struct LIBEXPORT VPoint{
    public:
        double x, y;
        VPoint(double x, double y);
    };
}

#endif /* VPOINT_H */