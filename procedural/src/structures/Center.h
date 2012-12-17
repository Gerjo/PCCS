#ifndef CENTER_H
#define CENTER_H

#include <CompileConfig.h>
#include <vector>

#include "Corner.h"
#include "Edge.h"
#include <phantom.h>
#include <utils/Maths.h>

using phantom::Vector3;
using std::vector;

namespace PGC{
    class LIBEXPORT Center{
    public:
        Center(Vector3* point);
        ~Center();
        Vector3* point;

        vector<Center*>    neighbours;
        vector<Edge*>      borders;
        vector<Corner*>    corners;
        vector<Corner*>    sortedCorners;
        vector<Edge*>      path;
        void binaryTraverse(Center* end);
        float getArea();
        int counter;
        int direction;
        int getDirection(Center* other);
        bool isBlocked;

        enum Direction{
            UP = 1,
            DOWN = 2,
            LEFT = 4,
            RIGHT = 8
        };    
    private:
        static Center* bar;
        void binaryTraverse(Center* start, Center* end);
        float area;
        void sortCorners(bool clockwise = true);

        static bool compareWith(const Corner* c1, const Corner* c2){
            Vector3 dir = *bar->point - *c1->point;
            float r1 = maths::directionToRotation(&dir);
            dir = *bar->point - *c2->point;
            float r2 = maths::directionToRotation(&dir);

            return (r1 < r2);
        }
    };

}

#endif /* CENTER_H */