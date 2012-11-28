#ifndef CORNER_H
#define CORNER_H

#include <CompileConfig.h>
#include <vector>

#include "Edge.h"
#include "nvoronoi/VPoint.h"


using namespace std;

namespace PGC{
    class LIBEXPORT Corner{
    public:
        Corner(void);

        VPoint* point;

        vector<Corner*> adjacent;
        vector<Edge*>   protrudes;
        vector<Center*> touches;
        bool border;
    };
}

#endif /* CORNER_H */