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

    srand(4);

    for(int i = 0; i < 100; i++){
        vertices->push_back(new VPoint(w * (double)((rand()/ (double) RAND_MAX)), h * (double)((rand()/ (double) RAND_MAX)) ) );
    }
    edges = v->GetEdges(vertices, w,h);

    for(vor::Edges::iterator i = edges->begin(); i!= edges->end(); ++i){
        if( (*i)->start == 0 ){
            std::cout << "Missing edges at begin\n";
            continue;
        }
        if( (*i)->end == 0 ){
            std::cout << "Missing edges at end!\n";
            continue;
        }	
    }
    buildGraph(vertices);
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
        c->border = (vpoint->x == 0 || vpoint->x == w || vpoint->y == 0 || vpoint->y == h);
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

void ProceduralDemo::update(const Time& time){
    Composite::update(time);    
}
void ProceduralDemo::drawVonoroi(){
    for(vor::Vertices::iterator i = vertices->begin(); i!=vertices->end(); ++i){
        getGraphics()
            .beginPath()
            .setFillStyle(phantom::Colors::RED).setLineStyle(phantom::Colors::RED)
            .rect((float)(*i)->x, (float)(*i)->y, 10, 10)
            .fill();
    }
    for(vor::Edges::iterator i = edges->begin(); i != edges->end(); ++i){

       getGraphics()
            .beginPath()
            .setFillStyle(phantom::Colors::WHITE).setLineStyle(phantom::Colors::WHITE)
            .line((*i)->left->x, (*i)->left->y, (*i)->right->x, (*i)->right->y)
            .fill();
        getGraphics()
            .beginPath()
            .setFillStyle(phantom::Colors::BLACK).setLineStyle(phantom::Colors::BLACK)
            .line((float)(*i)->start->x,(float)(*i)->start->y,(float)(*i)->end->x, (float)(*i)->end->y)
            .fill();

        for(Corner* c: corners){
            if(c->border){
                getGraphics()
                    .beginPath()
                    .setFillStyle(phantom::Colors::GREEN)
                    .rect(c->point->x, c->point->y, 10,10)
                    .fill();
                for(Center* t: c->touches){
                    getGraphics()
                    .beginPath()
                    .setFillStyle(phantom::Colors::BLUE)
                    .rect(t->point->x, t->point->y, 10,10)
                    .fill();
                }
            }
        }

        if((*i)->start->x > w || (*i)->start->y > h || (*i)->end->x > w || (*i)->end->y > h){
//            __asm{ int 3};
        }
    }
}

