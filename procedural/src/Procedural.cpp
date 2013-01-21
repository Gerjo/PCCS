#include "Procedural.h"
#include <graphics/shapes/Polygon.h>
#include "structures/fortune/voronoi.h"

Procedural::Procedural(): Composite(), mousePos(){
    worldWidth = worldHeight = 5000;

    worldSpace = nullptr;
    objectiveSpace = nullptr;
}  
Procedural::~Procedural(){
    getGraphics().clear();
    delete worldSpace;
    delete objectiveSpace;
}
vector<Data> Procedural::generateWorld(int width, int height, int numPlayers, int maxSpaces){
    worldWidth = width;
    worldHeight = height;

    generateWorldSpaces(maxSpaces);
    generateObjectiveSpaces(numPlayers);
    objectiveSpace->addChildDiagram(worldSpace);

    return buildJSON(objectiveSpace->centers);
}
vector<Data> Procedural::generateWorldSpaces(int maxSpaces){
    VoronoiDiagram* retval = new VoronoiDiagram(worldWidth,worldHeight,maxSpaces,3);
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
vector<Data> Procedural::generateObjectiveSpaces(int numPlayers){
    int points = (numPlayers * 2) - 1;
    VoronoiDiagram* retval = new VoronoiDiagram(worldWidth,worldHeight,points,10);

    if(objectiveSpace != nullptr) delete objectiveSpace;
    objectiveSpace = retval;

    return buildJSON(objectiveSpace->centers);
}

void Procedural::generatePaths(int numPlayer) {
    // Determin which cell is the largest and create 2 paths until the numPlayers is lower than 0.
    Center *largest = nullptr;
    for(Center *c : *objectiveSpace->centers) {
        if(largest == nullptr) {
            largest = c;
        }
        else if(largest->neighbours.size() > 2) {
            if(largest->getArea() < c->getArea() && c->neighbours.size()) {
                largest = c;
            }
        }
    }

    continueGeneratingPaths(largest, &numPlayer);
}

void Procedural::continueGeneratingPaths(Center *current, int *numPlayers, int *maxDepth) {
    if(maxDepth == nullptr)
        maxDepth = new int(*numPlayers / 2);
    --(*maxDepth);
    if(*maxDepth > 0) {
        int spawnposition[] = { (rand() % (current->children.size()) - 1), (rand() % (current->neighbours[0]->children.size() - 1)) };
        current->neighbours[0]->binaryTraverse(current->children[spawnposition[0]], current->children[spawnposition[1]]);

        --(*numPlayers);

        continueGeneratingPaths(current->neighbours[0], numPlayers, maxDepth);

        if(current->neighbours.size() >= 2 && numPlayers > 0) {
            current->neighbours[1]->binaryTraverse(current->children[spawnposition[0]], current->children[spawnposition[1]]);
            --(*numPlayers);
            continueGeneratingPaths(current->neighbours[0], numPlayers, maxDepth);
        }
    }
    else {
#ifdef _DEBUG
        cout << "No more paths to generate." << endl;
#endif
        return;
    }
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
                .fill();
        }
    }
}
