#include "ProceduralDemo.h"
#include <graphics/shapes/Polygon.h>
#include "structures/fortune/voronoi.h"
#include <list>
ProceduralDemo::ProceduralDemo(): GameState(), corners(0), centers(0),_edges(0), count(500){
    getDriver()->enableCamera(getDriver()->createCamera());
    w = getPhantomGame()->getWorldSize().x;
    h = getPhantomGame()->getWorldSize().y;

    v = new vor::VoronoiDiagramGenerator();
    vertices = new vector<Vector3>();
    srand(5);

    for(int i = 0; i < count; i++){
        vertices->push_back(Vector3(w * (float)((rand()/ (float) RAND_MAX)), h * (float)((rand()/ (float) RAND_MAX))) );
    }

    buildGraph(vertices);

    drawVonoroi();
}  
ProceduralDemo::~ProceduralDemo(){
}

void ProceduralDemo::buildGraph(vector<Vector3>* points){
    float* xval = new float[count];
    float* yval = new float[count];
    map<Vector3, Center*>* centerLookup;

    for(int i = 0; i < count; ++i){
        xval[i] = points->at(i).x;
        yval[i] = points->at(i).y;
    }
    v->generateVoronoi(xval,yval,count,0,w,0,h,0);
    centerLookup = &v->centerLookup;
    centers = &v->centers;
    corners = &v->corners;
    _edges = &v->edges;

    for(Corner* c : *corners){
        Vector3* p = c->point;
        if(p->x >= w || p->x <= 0 || p->y >= h || p->y <= 0){
            c->isBorder = true;
        }
    }

    delete[] xval, yval;
}

Corner* ProceduralDemo::makeCorner(Vector3& vect){
    Corner* c = new Corner();
    c->point = &vect;
    corners->push_back(c);
    return c;
}

void ProceduralDemo::relaxation(vector<Center*> centerList){
    /*double minx = 0 , miny = 0, maxx = 0, maxy = 0;
    double interval = 1;
    Vertices* region = new Vertices();
    double px = 0, py = 0;
    for(Center* center : centers){
    int size = 0;
    for(Corner* c : center->corners){
    ++size;
    px += c->point->x;
    py =+ c->point->y;
    }
    px /= size;
    py /= size;
    region->push_back(new VPoint(px, py));
    }
    buildGraph(region);*/
}

void ProceduralDemo::update(const PhantomTime& time){
    Composite::update(time);    

    MouseState* m = getDriver()->getInput()->getMouseState();
    mousePos = m->getPosition();
    getGraphics().clear();
    drawVonoroi();
}
bool ProceduralDemo::canDraw(Edge* e){
    /*VPoint a = *e->v0->point;
    VPoint b = *e->v1->point;

    double diff = sqrt((b.x - a.x)*(b.x - a.x) + (b.y - a.y)*(b.y - a.y));
    */
    return true;
}
void ProceduralDemo::drawVonoroi(){

    for(Edge* e : *_edges){
        /* voronoi edges */
        getGraphics().beginPath()
            .setFillStyle(phantom::Colors::BLACK)
            .line(*e->v0->point, *e->v1->point)
            .fill();
        /* delaunay edges */
        getGraphics().beginPath()
            .setFillStyle(phantom::Colors::WHITE)
            .line(*e->d0->point, *e->d1->point)
            .fill();

    }
    for(Center* center : *centers){
        for(Corner* c : center->corners){
            if(c->isBorder){
                for(Edge* e : center->borders){
                    getGraphics().beginPath()
                        .setFillStyle(phantom::Colors::RED)
                        .line(*e->v0->point, *e->v1->point)
                        .fill();
                }
            }
        }
    }

}

