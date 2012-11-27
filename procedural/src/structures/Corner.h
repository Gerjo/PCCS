#ifndef CORNER_H
#define CORNER_H

#include <CompileConfig.h>
#include "Edge.h"
#include "VPoint.h"
#include <vector>

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