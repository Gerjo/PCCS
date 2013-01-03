#include "Procedural.h"
#include <graphics/shapes/Polygon.h>
#include "structures/fortune/voronoi.h"

Procedural::Procedural(): Composite(){
    worldWidth = 5000;
    worldHeight = 5000;
}  
Procedural::~Procedural(){
    getGraphics().clear();
    delete worldSpace;
    delete objectiveSpace;
}

vector<Data> Procedural::generateWorld(int relaxCount){
    return buildJSON(true);
}
vector<Data> Procedural::generateWorldSpaces(){

}
vector<Data> Procedural::generateObjectiveSpaces(int numPlayers){
}

vector<Data> Procedural::buildJSON(bool useCenters){
    vector<Data> dataList;
    return dataList;
}

