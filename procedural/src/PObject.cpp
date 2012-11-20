#include "PObject.h"

PObject::PObject(): GameObject(){
    
    init();
    repaint();
}
void PObject::init(){
    w = 1000;
    v = new Voronoi();
    vertices = new PGC::Vertices();
    dir = new PGC::Vertices();

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
void PObject::update(const Time& time){
    GameObject::update(time);
    
}
void PObject::paint(){
    PGC::Vertices::iterator j = dir->begin();
    for(PGC::Vertices::iterator i = vertices->begin(); i != vertices->end(); ++i){
        (*i)->x += (*j)->x * w/50;
        (*i)->y += (*j)->y * w/50;
        if( (*i)->x > w ) (*j)->x *= -1;
        if( (*i)->x < 0 ) (*j)->x *= -1;

        if( (*i)->y > w ) (*j)->y *= -1;
        if( (*i)->y < 0 ) (*j)->y *= -1;
        ++j;
    }
    edges = v->getEdges(vertices,w,w);
    
    
    for(PGC::Vertices::iterator i = vertices->begin(); i!=vertices->end(); ++i){
        getGraphics().beginPath().setFillStyle(phantom::Colors::BLACK).setLineStyle(phantom::Colors::BLACK)
            .line(-1+2*(*i)->x - 1, -1+2*(*i)->y - 1, -1+2*(*i)->x +1,  -1+2*(*i)->y - 1)
            .line(-1+2*(*i)->x +1,  -1+2*(*i)->y - 1, -1+2*(*i)->x +1,  -1+2*(*i)->y + 1)
            .line(-1+2*(*i)->x +1,  -1+2*(*i)->y + 1, -1+2*(*i)->x -1, -1+2*(*i)->y + 1)
            .line(-1+2*(*i)->x -1, -1+2*(*i)->y + 1, -1+2*(*i)->x - 1, -1+2*(*i)->y - 1)
            .stroke().fill();
    }
    for(PGC::Edges::iterator i = edges->begin(); i != edges->end(); i++){
        getGraphics().beginPath().setFillStyle(phantom::Colors::BLACK).setLineStyle(phantom::Colors::BLACK)
        .line(-1+2*(*i)->start->x,  -1+2*(*i)->start->y, -1+2*(*i)->end->x, -1+2*(*i)->end->y)
        .stroke().fill();
        //getGraphics().moveTo(-1+2*(*i)->start->x/w,  -1+2*(*i)->start->y/w);
        //getGraphics().lineTo(-1+2*(*i)->end->x/w, -1+2*(*i)->end->y/w);
    }
    

}