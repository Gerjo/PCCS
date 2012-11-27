#ifndef PROCDEMO_H
#define PROCDEMO_H

#include <phantom.h> 
#include "structures/VEdge.h"
#include "structures/VParabola.h"
#include "structures/VEvent.h"
#include "structures/Voronoi.h"
#include "structures/VPoint.h"
#include "structures/Center.h"
#include "structures/Corner.h"
#include "structures/Edge.h"

using namespace PGC;
using namespace phantom;
using namespace vor;

class LIBEXPORT ProceduralDemo: public GameState{
public:
    ProceduralDemo();
    virtual ~ProceduralDemo();
    virtual void update(const Time& time);
    void buildGraph(Vertices* points);
    void drawVonoroi(); 
private:
    double w;
    double h;
    vector<Corner*> corners;
    vector<Center*> centers;
    vector<Edge*> _edges;
    Voronoi* v;
    vor::Vertices* vertices;
    vor::Vertices* dir;
    Edges* edges;
};

#endif /* PROCDEMO_H */
