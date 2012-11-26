#ifndef CENTER_H
#define CENTER_H

#include <CompileConfig.h>
#include <vector>

#include "Corner.h"
#include "Edge.h"
#include "VPoint.h"

using std::vector;

namespace PGC{
    class LIBEXPORT Center{
    public:
        Center(VPoint* point);

        VPoint* point;

        vector<Center*>    neighbours;
        vector<Edge*>      borders;
        vector<Corner*>    corners;
    };
}

#endif /* CENTER_H */