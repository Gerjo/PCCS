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
#include "VoronoiDiagram.h"

using namespace PGC;
using namespace phantom;
using std::vector;

class LIBEXPORT Procedural: public Composite{

public:
    Procedural();
    virtual ~Procedural();

    vector<Data>        generateObjectiveSpaces (int numPlayers);
    vector<Data>        generateWorldSpaces     ();
private:
    void            buildGraph          (vector<Vector3>* points);
    void            relaxation          (vector<Center*>* centerList);
    void            improveEdgeLength   ();

    vector<Data>        buildJSON(vector<Center*>* centerList);
private: //properties
    float worldWidth;
    float worldHeight;

    VoronoiDiagram* worldSpace, *objectiveSpace;
};

#endif /* PROCEDURAL_H */
