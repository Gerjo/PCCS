#include "ProceduralDemo.h"
#include <graphics/shapes/Polygon.h>
ProceduralDemo::ProceduralDemo(): GameState(){
    cout << "hello!" << endl;
    getDriver()->enableCamera(getDriver()->createCamera());
    foo = false;
    w = getPhantomGame()->getWorldSize().x;
    h = getPhantomGame()->getWorldSize().y;

    v = new Voronoi();
    vertices = new PGC::Vertices();
    dir = new PGC::Vertices();

    srand(time(NULL));

    for(int i = 0; i < 500; i++){
        vertices->push_back(new VPoint(w * (double)rand() /(double) RAND_MAX, h * (double)rand() / (double) RAND_MAX));
        dir->push_back(new VPoint(w * (double)rand()/(double)RAND_MAX - 0.5, w * (double)rand()/(double)RAND_MAX - 0.5));
    }
    edges = v->getEdges(vertices, w,h);

    for(PGC::Edges::iterator i = edges->begin(); i!= edges->end(); ++i){
        if( (*i)->start == 0 ){
            std::cout << "Missing edges at begin\n";
            continue;
        }
        if( (*i)->end == 0 ){
            std::cout << "Missing edges at end!\n";
            continue;
        }	
    }
}
ProceduralDemo::~ProceduralDemo(){
}
void ProceduralDemo::update(const Time& time){
    Composite::update(time);
    getGraphics().clear();
    drawVonoroi();
}
void ProceduralDemo::drawVonoroi(){
    if(true){

        for(PGC::Vertices::iterator i = vertices->begin(); i!=vertices->end(); ++i){
            getGraphics()
                .beginPath()
                .setFillStyle(phantom::Colors::RED).setLineStyle(phantom::Colors::RED)
                .rect((float)(*i)->x, (float)(*i)->y, 10, 10)
                .fill().stroke();
        }
        for(PGC::Edges::iterator i = edges->begin(); i != edges->end(); ++i){
            
            getGraphics()
                .beginPath()
                .setFillStyle(phantom::Colors::WHITE).setLineStyle(phantom::Colors::WHITE)
                .line((*i)->left->x, (*i)->left->y, (*i)->right->x, (*i)->right->y)
                .line( (*i)->right->x, (*i)->right->y, (*i)->left->x, (*i)->left->y)
                .stroke().fill();
            getGraphics()
                .beginPath()
                .setFillStyle(phantom::Colors::BLACK).setLineStyle(phantom::Colors::BLACK)
                .line((*i)->end->x, (*i)->end->y,(*i)->start->x,(*i)->start->y)
                .line((*i)->start->x, (*i)->start->y, (*i)->end->x, (*i)->end->y)
                .stroke().fill();
        }
        foo = true;
    }
}
