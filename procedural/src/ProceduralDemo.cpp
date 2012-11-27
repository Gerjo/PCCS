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

    srand(2);

    for(int i = 0; i < 500; i++){
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
    
    drawVonoroi();
}
ProceduralDemo::~ProceduralDemo(){
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
        if((*i)->start->x > w || (*i)->start->y > h || (*i)->end->x > w || (*i)->end->y > h){
//            __asm{ int 3};
        }
    }
}

