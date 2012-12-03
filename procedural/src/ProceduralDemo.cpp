#include "ProceduralDemo.h"
#include <graphics/shapes/Polygon.h>
#include "structures/fortune/voronoi.h"
#include <list>
ProceduralDemo::ProceduralDemo(): GameState(), corners(0), centers(0),_edges(0){
    getDriver()->enableCamera(getDriver()->createCamera());
    w = getPhantomGame()->getWorldSize().x;
    h = getPhantomGame()->getWorldSize().y;

    v = new vor::VoronoiDiagramGenerator();
    vertices = new vector<Vector3*>();
    srand(2);

    for(int i = 0; i < 50; i++){
        vertices->push_back(new Vector3(w * (float)((rand()/ (float) RAND_MAX)), h * (float)((rand()/ (float) RAND_MAX))) );
    }

    buildGraph(vertices);
}  
ProceduralDemo::~ProceduralDemo(){
}

void ProceduralDemo::buildGraph(vector<Vector3*>* points){
    Center *p;
    float xval[50];
    float yval[50];
    int i = 0;
    for(Vector3* vec : *points){
        xval[i] = vec->x;
        yval[i] = vec->y;
        ++i;
    }

    v->generateVoronoi(xval,yval,50,0,w,0,h,1);

    map<Vector3*, Center*> centerLookup;
    map<int, list<Corner*>> cornerMap;

    for(vector<Vector3*>::iterator i = points->begin(); i != points->end(); i++){
        p = new Center(*i);
        centers.push_back(p);
        centerLookup[*i] = p;
    }

    std::function<Corner*(Vector3*, map<int, list<Corner*>>*)> makeCorner = [this](Vector3* vpoint, map<int,list<Corner*>>* cornerMap)-> Corner*{
        if(vpoint == 0) return 0;

        for(int bucket = (int)vpoint->x -1; bucket <= (int)vpoint->x +1; bucket++){
            if(cornerMap->find(bucket) != cornerMap->end()){
                for(Corner* c : cornerMap->find(bucket)->second){
                    float dx = vpoint->x - c->point->x;
                    float dy = vpoint->y - c->point->y;
                    if(dx*dx + dy*dy < 1e-6){
                        return c;
                    }
                }
            }
        }
        int bucket = (int)vpoint->x;
        if(cornerMap->find(bucket) == cornerMap->end()){
            cornerMap->insert(map<int,list<Corner*>>::value_type(bucket,list<Corner*>()));
        }
        Corner* c = new Corner();
        c->point = vpoint;
        c->border = (vpoint->x <= 0 || vpoint->x >= w || vpoint->y <= 0 || vpoint->y >= h);
        this->corners.push_back(c);
        cornerMap->find(bucket)->second.push_back(c);
        return c;
    };
    v->resetIterator();
    v->resetDelaunayEdgesIterator();
    int counter = 0;

    while( counter < v->nedges){
        Vector3* dedge[2] = {new Vector3(), new Vector3()};
        Vector3* vedge[2] = {new Vector3(), new Vector3()};

        v->getNextDelaunay(dedge[0]->x,dedge[0]->y,dedge[1]->x,dedge[1]->y);
        v->getNext(vedge[0]->x,vedge[0]->y,vedge[1]->x,vedge[1]->y);

        Edge* edge = new Edge();
        _edges.push_back(edge);
        
        edge->v0 = makeCorner(vedge[0], &cornerMap);
        edge->v1 = makeCorner(vedge[1], &cornerMap);
        map<Vector3*, Center*>::iterator testit = centerLookup.find(dedge[0]);
        edge->d0 = centerLookup.find(dedge[0])->second;
        edge->d1 = centerLookup.find(dedge[1])->second;
        
        if (edge->d0 != 0) { edge->d0->borders.push_back(edge); }
        if (edge->d1 != 0) { edge->d1->borders.push_back(edge); }
        if (edge->v0 != 0) { edge->v0->protrudes.push_back(edge); }
        if (edge->v1 != 0) { edge->v1->protrudes.push_back(edge); }

        // Centers point to centers.
        if(edge->d0 != 0 && edge->d1 != 0){
            edge->d0->neighbours.push_back(edge->d1);
            edge->d1->neighbours.push_back(edge->d0);
        }
        // Corners point to corners
        if(edge->v0 != 0 && edge->v1 != 0){
            edge->v0->adjacent.push_back(edge->v1);
            edge->v1->adjacent.push_back(edge->v0);
        }

        // Centers point to corners
        if(edge->d0 != 0){
            edge->d0->corners.push_back(edge->v0);
            edge->d0->corners.push_back(edge->v1);
        }
        if(edge->d1 != 0){
            edge->d1->corners.push_back(edge->v0);
            edge->d1->corners.push_back(edge->v1);
        }

        // corners point to centers
        if(edge->v0 != 0){
            edge->v0->touches.push_back(edge->d0);
            edge->v0->touches.push_back(edge->d1);
        }
        if(edge->v1 != 0){
            edge->v1->touches.push_back(edge->d0);
            edge->v1->touches.push_back(edge->d1);
        }
        ++counter;
    }

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
    if(m->isButtonDown(Buttons::LEFT_MOUSE)){
        cout << m->getPosition().toString2() << endl;
    }

}
bool ProceduralDemo::canDraw(Edge* e){
    /*VPoint a = *e->v0->point;
    VPoint b = *e->v1->point;

    double diff = sqrt((b.x - a.x)*(b.x - a.x) + (b.y - a.y)*(b.y - a.y));
    */
    return true;
}
void ProceduralDemo::drawVonoroi(){
    for(Edge* e : _edges){
        getGraphics()
            .beginPath()
            .setFillStyle(phantom::Colors::BLACK).setLineStyle(phantom::Colors::BLACK)
            .line(e->v0->point->x, e->v0->point->y, e->v1->point->x, e->v1->point->y) // voronoi edges
            //.line(e->d0->point->x, e->d0->point->y, e->d1->point->x, e->d1->point->y) // delaunay edges
            .fill();
        getGraphics()
            .beginPath()
            .setFillStyle(phantom::Colors::WHITE).setLineStyle(phantom::Colors::WHITE)
            //.line(e->v0->point->x, e->v0->point->y, e->v1->point->x, e->v1->point->y) // voronoi edges
            //.line(e->d0->point->x, e->d0->point->y, e->d1->point->x, e->d1->point->y) // delaunay edges
            .fill();

    }
    for(Center* c : centers){
        getGraphics()
            .beginPath()
            .setFillStyle(phantom::Colors::RED).setLineStyle(phantom::Colors::RED)
            .rect(c->point->x, c->point->y,10,10)
            .fill();
    }
    /*for(Corner* c : corners){

    getGraphics()
    .beginPath();
    if(c->border){
    getGraphics()
    .setFillStyle(phantom::Colors::GREEN).setLineStyle(phantom::Colors::GREEN);
    }else {
    getGraphics()
    .setFillStyle(phantom::Colors::BLUE).setLineStyle(phantom::Colors::BLUE);
    }
    getGraphics()
    .rect(c->point->x, c->point->y,10,10)
    .fill();
    }

    for(Center* c : centers){
    for(Corner* corner : c->corners){
    if(corner->border){
    for(Edge* e : c->borders){
    getGraphics()
    .beginPath()
    .setFillStyle(phantom::Colors::RED).setLineStyle(phantom::Colors::RED)
    .line(e->v0->point->x, e->v0->point->y, e->v1->point->x, e->v1->point->y)
    .fill();
    }
    }
    }
    }*/
}

