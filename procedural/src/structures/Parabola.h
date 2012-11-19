#ifndef PARABOLA_H
#define PARABOLA_H

#include <CompileConfig.h>

#include "VPoint.h"
#include "Edge.h"

namespace PGC{
    class VEvent;

    class LIBEXPORT Parabola{
    public:
        bool isLeaf;
        VPoint* site;
        Edge* edge;
        VEvent* cEvent;
        Parabola* parent;

        Parabola();
        Parabola(VPoint* p);
        void setLeft(Parabola* p);
        void setRight(Parabola* p);

        Parabola* left();
        Parabola* right();
    public: //statics
        static Parabola* getLeft(Parabola* p);
        static Parabola* getRight(Parabola* p);
        static Parabola* getLeftParent(Parabola* p);
        static Parabola* getRightParent(Parabola* p);
        static Parabola* getLeftChild(Parabola* p);
        static Parabola* getRightChild(Parabola* p);
    private:
        Parabola* _left;
        Parabola* _right;
    };
}


#endif /* PARABOLA_H */