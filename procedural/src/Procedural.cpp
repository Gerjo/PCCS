#include "Procedural.h"
#include <graphics/shapes/Polygon.h>
#include "structures/fortune/voronoi.h"

Procedural::Procedural(): Composite(){
    worldWidth = 5000;
    worldHeight = 5000;
}  
Procedural::~Procedural(){
    getGraphics().clear();
    //delete worldSpace;
    //delete objectiveSpace;
}
vector<Data> Procedural::generateWorldSpaces(){
    VoronoiDiagram* retval = new VoronoiDiagram(worldWidth,worldHeight,500,3);
    vector<Center*>* centers = retval->centers;
    float avg = 0;
    int count = 0;
    for(Center* c : *centers){
        avg += c->getArea();
        ++count;
    }
    avg /= count;
    for(Center* c : *centers){
        if(c->getArea() < avg){
            c->isBlocked = true;
        }
    }
    cout << "average area: " << avg << endl << endl;
    return buildJSON(retval->centers);
}
vector<Data> Procedural::generateObjectiveSpaces(int numPlayers){
    int points = (numPlayers * 2) - 1;
    VoronoiDiagram* retval = new VoronoiDiagram(worldWidth,worldHeight,points,3);
    VoronoiDiagram* world = new VoronoiDiagram(worldWidth,worldHeight,500,3);
    retval->addChildDiagram(world);
    return buildJSON(world->centers);
}
vector<Data> Procedural::buildJSON(vector<Center*>* centerList){
    vector<Data> dataList;
    for(Center* c : *centerList){
        if(c->isBlocked){
            float x = (c->point->x);
            float y = (c->point->y);
            Data data;
            data("type") = "tree";
            data("height")   = 100;
            data("width")    = 106;
            data("x")        = x;
            data("y")        = y;
            dataList.push_back(data);
        }
    }
    return dataList;
}

