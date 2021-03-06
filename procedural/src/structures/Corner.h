#ifndef CORNER_H
#define CORNER_H

#include <CompileConfig.h>
#include <vector>

#include "Edge.h"
#include <phantom.h>

using phantom::Vector3;

using namespace std;

namespace PGC{
    class LIBEXPORT Corner{
    public:
        Corner(void);
        ~Corner();
        Vector3* point;

        vector<Corner*> adjacent;
        vector<Edge*>   protrudes;
        vector<Center*> touches;
        bool isBorder;
        int index;
    };
}

#endif /* CORNER_H */