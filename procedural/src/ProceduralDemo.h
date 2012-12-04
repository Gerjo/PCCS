#ifndef PROCDEMO_H
#define PROCDEMO_H

#include <phantom.h> 

#include "structures/Center.h"
#include "structures/Corner.h"
#include "structures/Edge.h"
#include "structures/fortune/voronoi.h"
#include <vector>

using namespace PGC;
using namespace phantom;
using std::vector;

class LIBEXPORT ProceduralDemo: public GameState{

public:
    ProceduralDemo();
    virtual ~ProceduralDemo();
    virtual void update(const PhantomTime& time);
    
    void buildGraph(vector<Vector3>* points);
    void relaxation(vector<Center*> centerList);
    void drawVonoroi();
private:
    double w;
    double h;
    const unsigned int const count;
    Vector3 mousePos;
    vector<Corner*>* corners;
    vector<Center*>* centers;
    vector<Edge*>* _edges;
    vor::VoronoiDiagramGenerator * v;
    vector<Vector3>* vertices;
};

#endif /* PROCDEMO_H */
