#ifndef CENTER_H
#define CENTER_H

#include <CompileConfig.h>
#include <vector>

#include "Corner.h"
#include "Edge.h"
#include <phantom.h>

using phantom::Vector3;
using std::vector;

namespace PGC{
    class LIBEXPORT Center{
    public:
        Center(Vector3* point);

        Vector3* point;

        vector<Center*>    neighbours;
        vector<Edge*>      borders;
        vector<Corner*>    corners;
        vector<Edge*>      path;
        void binaryTraverse(Center* end);
        
        int direction;
        int getDirection(Center* other);
        static enum Direction{
            UP = 1,
            DOWN = 2,
            LEFT = 4,
            RIGHT = 8
        };    
    private:
        void binaryTraverse(Center* start, Center* end);
    };

}

#endif /* CENTER_H */