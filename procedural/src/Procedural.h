#ifndef PROCEDURAL_H
#define PROCEDURAL_H

#include <vector>

#include <phantom.h> 
#include <yaxl.h>

#include <sharedlib/sharedlib.h>
#include <sharedlib/CompileConfig.h>
#include <sharedlib/serialization/Data.h>

#include "structures/fortune/voronoi.h"
#include "structures/Center.h"
#include "structures/Corner.h"
#include "structures/Edge.h"


using namespace PGC;
using namespace phantom;
using std::vector;

class LIBEXPORT Procedural: public Composite{

public:
    Procedural();
    virtual ~Procedural();
    
    vector<Data*> generateWorld(int relaxCount);
private:
    void            buildGraph          (vector<Vector3>* points);
    void            relaxation          (vector<Center*> centerList);
    void            improveEdgeLength   ();

    vector<Data*>   buildJSON           (bool centers);
private: //properties
    unsigned int const count;

    float worldWidth;
    float worldHeight;

    vector<Vector3>*    vertices;
    vector<Corner*>*    corners;
    vector<Center*>*    centers;
    vector<Edge*>*      edges;

    vor::VoronoiDiagramGenerator* voronoiDiagram;
    
};

#endif /* PROCEDURAL_H */
