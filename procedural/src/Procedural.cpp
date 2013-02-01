#include "Procedural.h"
#include <graphics/shapes/Polygon.h>
#include "structures/fortune/voronoi.h"

Procedural::Procedural(): Composite(), mousePos(){
    worldWidth = worldHeight = 5000;

    worldSpace = nullptr;
    objectiveSpace = nullptr;
    searchGraph = nullptr;
}  
Procedural::~Procedural(){
    getGraphics().clear();
    delete worldSpace;
    delete objectiveSpace;
    delete searchGraph;
}
vector<Data> Procedural::generateWorld(int width, int height, int numPlayers, int maxSpaces){
    worldWidth = width;
    worldHeight = height;

    generateWorldSpaces(maxSpaces);
    generateObjectiveSpaces(numPlayers);
    objectiveSpace->addChildDiagram(worldSpace);
    divideSpawnCells(objectiveSpace->centers);
    return buildJSON(objectiveSpace->centers);
}

void Procedural::buildSearchGraph(int numPlayers){
    vector<FF::Node*> nodes;

    int maxNodes = (numPlayers*2) -1;

    for(int i = 0; i < maxNodes; ++i){
        FF::Node* n = new FF::Node('c');
        nodes.push_back(n);
        searchGraph->AddNode(n);
    }

    FF::Node* n = *nodes.end();

}

vector<Data> Procedural::generateObjectiveSpaces(int numPlayers){
    int points = (numPlayers * 2) - 1;
    VoronoiDiagram* retval = new VoronoiDiagram(worldWidth,worldHeight,points,5);

    if(objectiveSpace != nullptr) delete objectiveSpace;
    objectiveSpace = retval;

    return buildJSON(objectiveSpace->centers);
}
vector<Data> Procedural::generateWorldSpaces(int maxSpaces){
    VoronoiDiagram* retval = new VoronoiDiagram(worldWidth,worldHeight,maxSpaces,10);
    vector<Center*>* centers = retval->centers;
    float avg = 0;
    int count = 0;
    for(Center* c : *centers){
        avg += c->getArea();
        ++count;
    }
    avg /= count;
    count = 0;
    for(Center* c : *centers){
        if(c->getArea() < avg){
            //c->isBlocked = true;
            ++count;
        }
    }
    cout << "average area: " << avg << endl << endl;
    if(worldSpace != nullptr) delete worldSpace;
    worldSpace = retval;
    return buildJSON(worldSpace->centers);
}

Data Procedural::toData() {
    Data data;
    data("a") = "b";
    return data;
}

vector<Data> Procedural::buildJSON(vector<Center*>* centerList){
    vector<Data> dataList;
    for(Center* c : *centerList){
        if(c->getAreaWithNeighbours() > 130){
            float x = (c->point->x);
            float y = (c->point->y);
            Data data;
            data("type") = "ObjectiveX";
            data("height")   = 100;
            data("width")    = 106;
            data("x")        = x;
            data("y")        = y;
            dataList.push_back(data);
        }
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
void Procedural::divideSpawnCells(vector<Center*>* centerList){
    Center* finalStage = findGreatestCell(centerList);

    //binaryDivide(finalStage, 16);

}
void Procedural::binaryDivide(Center* center, int count){
    if(count <= 0) return;
    
}
Center* Procedural::findGreatestCell(vector<Center*>* centerList){
    Center* retval = 0;
    for(Center* c : *centerList){
        if(retval == 0){
            retval = c;
            continue;
        }
        if(retval->getArea() < c->getArea()) retval = c;
    }
    return retval;
}
void Procedural::update(const phantom::PhantomTime& time){
    Composite::update(time);
    MouseState* m = getDriver()->getInput()->getMouseState();
    mousePos = m->getPosition();
    if(m->isButtonDown(Buttons::LEFT_MOUSE)){
        getGraphics().clear();
        paint();
    }
}
void Procedural::paint(){
    for(Center* topCenter: *objectiveSpace->centers){
        getGraphics().beginPath().setFillStyle(phantom::Colors::GREEN)
            .rect(topCenter->point->x,topCenter->point->y,10,10)
            .fill();
        if(topCenter->point->distanceToSq(mousePos) < 200){
            for(Center* child: topCenter->children){
                for(Edge* e: child->borders){
                    if(child->isBorder){
                        if(child->isBlocked){
                            getGraphics().beginPath().setFillStyle(phantom::Colors::RED)
                                .line(*e->v0->point,*e->v1->point)
                                .fill();
                        }else{
                            getGraphics().beginPath().setFillStyle(phantom::Colors::BLUE)
                                .line(*e->v0->point,*e->v1->point)
                                .fill();
                        }

                    }else{
                        getGraphics().beginPath().setFillStyle(phantom::Colors::GREEN)
                            .line(*e->v0->point,*e->v1->point)
                            .fill();
                    }
                }
                getGraphics().beginPath().setFillStyle(phantom::Colors::RED)
                    .rect(child->point->x,child->point->y,10,10)
                    .fill();
            }
        }
        for(Edge* e : topCenter->borders){
           getGraphics().beginPath().setFillStyle(phantom::Colors::BLACK)
                .line(*e->v0->point,*e->v1->point)
                .line(*e->v0->point,*e->v1->point)
                .fill();
         getGraphics().beginPath().setFillStyle(phantom::Colors::HOTPINK)
                .line(*e->d0->point,*e->d1->point)
                .line(*e->d0->point,*e->d1->point)
                .fill();
        }
    }
}
