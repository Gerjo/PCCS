#ifndef PROCDEMO_H
#define PROCDEMO_H

#include <phantom.h> 
#include "structures/Edge.h"
#include "structures/Parabola.h"
#include "structures/VEvent.h"
#include "structures/Voronoi.h"
#include "structures/VPoint.h"
#include "PObject.h"
using namespace phantom;
using namespace PGC;

class LIBEXPORT ProceduralDemo: public GameState{
public:
    ProceduralDemo();
    virtual ~ProceduralDemo();
    virtual void update(const Time& time);
    
    void drawVonoroi(); 
private:
    double w;
    bool foo;
    PObject* po;
    Voronoi* v;
    PGC::Vertices* vertices;
    PGC::Vertices* dir;
    Edges* edges;
};

#endif /* PROCDEMO_H */
