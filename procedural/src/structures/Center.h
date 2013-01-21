#ifndef CENTER_H
#define CENTER_H

#include <sharedlib/CompileConfig.h>
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
        ~Center();

        static void populateChildren(vector<Center*>* childList, vector<Center*>* centerList);
        static void setAsBorder(vector<Center*>* childList);
        
        void closeBorder(Center* neighbour);
        Vector3* point;

        vector<Center*>    neighbours;
        vector<Edge*>      borders;
        vector<Corner*>    corners;
        vector<Corner*>    sortedCorners;
        vector<Edge*>      path;

        vector<Center*> children;

        Center* getParent();
        void binaryTraverse(Center* end);
        float getArea();
        int counter;
        int direction;
        int getDirection(Center* other);
        void binaryTraverse(Center* start, Center* end);
        bool isBlocked;
        bool isBorder;
        bool isSpawnArea;

        enum Direction{
            UP = 1,
            DOWN = 2,
            LEFT = 4,
            RIGHT = 8
        };    
    private:
        Center* parent;
        Center* neighbouringParent;
        static Center* bar;
        float area;

        void sortCorners(bool clockwise = true);

        static bool compareWith(const Corner* c1, const Corner* c2){
            Vector3 dir = *bar->point - *c1->point;
            float r1 = dir.getAngleXOY();
            dir = *bar->point - *c2->point;
            float r2 = dir.getAngleXOY();

            return (r1 < r2);
        }
    };

}

#endif /* CENTER_H */