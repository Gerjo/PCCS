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
#include "graph/Graph.h"
using namespace PGC;
using phantom::Composite;
using phantom::Vector3;
using std::vector;

class LIBEXPORT Procedural : public Composite{

public:
    Procedural();
    virtual ~Procedural();
    virtual void paint();
    virtual void update(const phantom::PhantomTime& time);
    vector<Data>        generateWorld(int width, int height, int numPlayers, int maxSpaces);
    vector<Data>        generateObjectiveSpaces (int numPlayers);
    vector<Data>        generateWorldSpaces     (int maxSpaces);
    Data                toData();
    void                fromData(const std::string& json);

private:
    void            buildGraph              (vector<Vector3>* points);
    void            relaxation              (vector<Center*>* centerList);
    void            improveEdgeLength       ();
    void            buildSearchGraph        (int numPlayers);
    Center*         findRandomChild         (Center *parent);

    vector<Data>        buildJSON(vector<Center*>* centerList);
    void                divideSpawnCells(vector<Center*>* centerList);
    void                binaryDivide(Center* center, int count);
    Center*             findGreatestCell(vector<Center*>* centerList);
private: //properties
    int worldWidth;
    int worldHeight;
    Vector3 mousePos;
    int count;
    VoronoiDiagram* worldSpace, *objectiveSpace;
    FF::Graph* searchGraph;
};

#endif /* PROCEDURAL_H */
