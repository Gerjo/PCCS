#include "ProceduralDemo.h"
#include <graphics/shapes/Polygon.h>
ProceduralDemo::ProceduralDemo(): GameState(){
    cout << "hello!" << endl;
    getDriver()->enableCamera(getDriver()->createCamera());
    w = getPhantomGame()->getWorldSize().x;
    h = getPhantomGame()->getWorldSize().y;

    v = new Voronoi();
    vertices = new vor::Vertices();
    dir = new vor::Vertices();

    srand(10);

    for(int i = 0; i < 50; i++){
        vertices->push_back(new VPoint(w * (double)((rand()/ (double) RAND_MAX)), h * (double)((rand()/ (double) RAND_MAX)) ) );
    }
    
    buildGraph(vertices);
    relaxation(centers);
    buildGraph(vertices);
   /* relaxation(centers);
    buildGraph(vertices);*/

    drawVonoroi();

}
ProceduralDemo::~ProceduralDemo(){
}

void ProceduralDemo::buildGraph(Vertices* points){
    Center *p;
    Edges* vEdges = v->GetEdges(points,w,h);
    map<VPoint*, Center*> centerLookup;
    map<int, list<Corner*>> cornerMap;

    for(Vertices::iterator i = points->begin(); i != points->end(); i++){
        p = new Center(*i);
        centers.push_back(p);
        centerLookup[*i] = p;
    }

    std::function<Corner*(VPoint*, map<int, list<Corner*>>*)> makeCorner = [this](VPoint* vpoint, map<int,list<Corner*>>* cornerMap)-> Corner*{
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

    for(Edges::iterator i = vEdges->begin(); i != vEdges->end(); i++){
        VPoint* dedge[2] = {(*i)->left, (*i)->right};
        VPoint* vedge[2] = {(*i)->start, (*i)->end};

        Edge* edge = new Edge();
        _edges.push_back(edge);

        edge->v0 = makeCorner(vedge[0], &cornerMap);
        edge->v1 = makeCorner(vedge[1], &cornerMap);
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
    }

}

void ProceduralDemo::relaxation(vector<Center*> centerList){
    double minx = 0 , miny = 0, maxx = 0, maxy = 0;
    double interval = 1;
    Vertices* region = new Vertices();

    for(Center* center : centerList){
        for(Corner* c : center->corners){
            if(minx == 0) minx = c->point->x;
            else minx = (c->point->x < minx)? c->point->x : minx;

            if(miny == 0) miny = c->point->y;
            else miny = (c->point->y < miny)? c->point->y : miny;

            if(maxx == 0) maxx = c->point->x;
            else maxx = (c->point->x > maxx)? c->point->x : maxx;

            if(maxy == 0) maxy = c->point->y;
            else maxy = (c->point->y > maxy)? c->point->y : maxy;
        }
        
        for(double i = minx; i < maxx; i += interval){
            for(double j = miny; i < maxy; j+= interval){
                region->push_back(new VPoint(i,j));
            }
        }
        float px = 0, py = 0;
        for(Vertices::iterator i = region->begin(); i != region->end(); ++i){
            px += (*i)->x;
            py += (*i)->y;
        }
        px /= (double) region->size();
        py /= (double) region->size();
    }

}

void ProceduralDemo::update(const Time& time){
    Composite::update(time);    
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
            .line(e->d0->point->x, e->d0->point->y, e->d1->point->x, e->d1->point->y) // delaunay edges
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
    }
}

