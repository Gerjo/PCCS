#ifndef PROCDEMO_H
#define PROCDEMO_H

#include <phantom.h> 
#include <glut/GLUTDriver.h>
#include <yaxl.h>
#include <sharedlib/sharedlib.h>
#include <sharedlib/CompileConfig.h>
#include "structures/Center.h"
#include "structures/Corner.h"
#include "structures/Edge.h"
#include "structures/fortune/voronoi.h"
#include <sharedlib/serialization/Data.h>
#include <vector>

using namespace PGC;
using namespace phantom;
using std::vector;

class LIBEXPORT ProceduralDemo: public GameState{

public:
    ProceduralDemo();
    vector<Data*> generateWorld(int relaxCount);
    virtual ~ProceduralDemo();
    virtual void update(const PhantomTime& time);
private:
    vector<Data*> buildJSON();
    void buildGraph(vector<Vector3>* points);
    void relaxation(vector<Center*> centerList);
    void drawVonoroi();
    double w;
    double h;
    unsigned int const count;
    bool isUp;
    Center *start, *end, *temp;
    Vector3 mousePos;
    vector<Corner*>* corners;
    vector<Center*>* centers;
    vector<Edge*>* _edges;
    vor::VoronoiDiagramGenerator * v;
    vector<Vector3>* vertices;
    Camera* camera;
};

#endif /* PROCDEMO_H */
