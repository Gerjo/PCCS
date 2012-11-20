#include "ProceduralDemo.h"
#include <graphics/shapes/Polygon.h>
ProceduralDemo::ProceduralDemo(): GameState(){
    cout << "hello!" << endl;
    getDriver()->enableCamera(getDriver()->createCamera());
    foo = false;
    w = 1000;
    v = new Voronoi();
    vertices = new PGC::Vertices();
    dir = new PGC::Vertices();

    srand(time(NULL));

    for(int i = 0; i < 50; i++){
        vertices->push_back(new VPoint(w * (double)rand()/(double)RAND_MAX, w * (double)rand()/(double)RAND_MAX));
        dir->push_back(new VPoint(w * (double)rand()/(double)RAND_MAX - 0.5, w * (double)rand()/(double)RAND_MAX - 0.5));
    }
    edges = v->getEdges(vertices, w, w);

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
    //getGraphics().beginPath().setFillStyle(phantom::Colors::WHITE).rect(Box3(50,50,100,100)).fill().stroke();
}
void ProceduralDemo::drawVonoroi(){
    if(true){

        

        
        for(PGC::Vertices::iterator i = vertices->begin(); i!=vertices->end(); ++i){
           /* getGraphics().beginPath().setFillStyle(phantom::Colors::BLACK).setLineStyle(phantom::Colors::BLACK)
                .line(-1+2*(*i)->x - 1, -1+2*(*i)->y - 1, -1+2*(*i)->x +1, -1+2*(*i)->y - 1)
                .line(-1+2*(*i)->x + 1, -1+2*(*i)->y - 1, -1+2*(*i)->x +1, -1+2*(*i)->y + 1)
                .line(-1+2*(*i)->x + 1, -1+2*(*i)->y + 1, -1+2*(*i)->x -1, -1+2*(*i)->y + 1)
                .line(-1+2*(*i)->x - 1, -1+2*(*i)->y + 1, -1+2*(*i)->x -1, -1+2*(*i)->y - 1)
                .stroke().fill();*/
            getGraphics()
                .beginPath()
                .setFillStyle(phantom::Colors::RED).setLineStyle(phantom::Colors::RED)
                .rect((*i)->x, (*i)->y, 10, 10)
                .fill().stroke();
        }
        for(PGC::Edges::iterator i = edges->begin(); i != edges->end(); ++i){
            /*getGraphics().beginPath().setFillStyle(phantom::Colors::BLACK).setLineStyle(phantom::Colors::BLACK)
                .line(-1+2*(*i)->left->x, -1+2*(*i)->left->y, -1+2*(*i)->right->x, -1+2*(*i)->right->y)
                .stroke().fill();
            getGraphics().beginPath()
                .setFillStyle(Colors::WHITE).setLineStyle(Colors::WHITE)
                .line(-1+2*(*i)->start->x, -1+2*(*i)->start->y, -1+2*(*i)->end->x, -1+2*(*i)->end->y)
                .stroke().fill();*/
            getGraphics()
                .beginPath()
                .setFillStyle(phantom::Colors::WHITE).setLineStyle(phantom::Colors::WHITE)
                .line((*i)->right->x, (*i)->right->y, (*i)->left->x, (*i)->left->y)
                .stroke().fill();
            getGraphics()
                .beginPath()
                .setFillStyle(phantom::Colors::BLACK).setLineStyle(phantom::Colors::BLACK)
                .line((*i)->start->x,(*i)->start->y,(*i)->end->x, (*i)->end->y)
                .stroke().fill();
           
        }
        foo = true;
    }
}
