#ifndef EDGE_H
#define EDGE_H

#include <sharedlib/CompileConfig.h>

namespace PGC{
    class Site;

    class LIBEXPORT Edge{
    public:
        Edge();
    private:
        float a, b, c;
        Site* ep;
        Site* reg;
        unsigned int _edgeNum;
    };
}

#endif /* SITE_H */