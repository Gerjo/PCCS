#ifndef PROCDEMO_H
#define PROCDEMO_H

#include <phantom.h> 
#include "structures/nvoronoi/VEdge.h"
#include "structures/nvoronoi/VParabola.h"
#include "structures/nvoronoi/VEvent.h"
#include "structures/nvoronoi/Voronoi.h"
#include "structures/nvoronoi/VPoint.h"
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
    virtual void update(const phantom::PhantomTime& time);
    void buildGraph(Vertices* points);
    void relaxation(vector<Center*> centerList);
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
