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

void Procedural::generatePaths(int numPlayer) {
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

    continueGeneratingPaths(largest, &numPlayer, numPlayer / 2);
}

void Procedural::continueGeneratingPaths(Center *current, int *numPlayers, int maxDepth) {
    --maxDepth;

    if(maxDepth > 0) {
        int spawnposition[] = { (rand() % current->children.size()), (rand() % current->neighbours[0]->children.size()) };

        current->neighbours[0]->children[spawnposition[1]]->binaryTraverse(nullptr, current->children[spawnposition[0]]);

        --(*numPlayers);

        current->children[spawnposition[0]]->isStart = true;


        continueGeneratingPaths(current->neighbours[0], numPlayers, maxDepth);

        if(current->neighbours.size() >= 2 && numPlayers > 0) {
            spawnposition[1] = (rand() % current->neighbours[1]->children.size());
            current->neighbours[1]->children[spawnposition[1]]->binaryTraverse(nullptr, current->children[spawnposition[0]]);

            --(*numPlayers);

            continueGeneratingPaths(current->neighbours[1], numPlayers, maxDepth);
        }
    }
    else {
#ifdef _DEBUG
        cout << "No more paths to generate." << endl;
#endif
        return;
    }
}

vector<Data> Procedural::generateObjectiveSpaces(int numPlayers){
    int points = (numPlayers * 2) - 1;
    VoronoiDiagram* retval = new VoronoiDiagram(worldWidth,worldHeight,points,10);

    if(objectiveSpace != nullptr) delete objectiveSpace;
    objectiveSpace = retval;

    return buildJSON(objectiveSpace->centers);
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

void Procedural::divideSpawnCells(vector<Center*>* centerList){
    Center* finalStage = findGreatestCell(centerList);

    vector<Center*> list = finalStage->neighbours;
    Center* tempval = findGreatestCell(&list);
    tempval->nextStage = finalStage;
    list.erase(find(list.begin(),list.end(),tempval));
    tempval = findGreatestCell(&list);
    tempval->nextStage = finalStage;
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
        //getGraphics().beginPath().setFillStyle(phantom::Colors::GREEN)
        //    .rect(topCenter->point->x,topCenter->point->y,10,10)
        //    .fill();
        if(topCenter->point->distanceToSq(mousePos) < 200 || true){
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

                if(child->isEnd != nullptr) {
                    getGraphics().beginPath().setFillStyle(phantom::Colors::BLACK)
                        .line(*child->point, *child->isEnd->point).fill();
                }
                else if(child->isStart) {
                    getGraphics().beginPath().setFillStyle(phantom::Colors::MIDNIGHTBLUE)
                        .rect(child->point->x, child->point->y, 15,15).fill();
                }
                else if(child->isPath != nullptr) {
                    getGraphics().beginPath().setFillStyle(phantom::Colors::WHITE)
                        .line(*child->point, *child->isPath->point).fill();
                }
                else {
                    //getGraphics().beginPath().setFillStyle(phantom::Colors::RED)
                    //    .rect(child->point->x,child->point->y,10,10)
                    //    .fill();
                }
            }
        }
        //for(Edge* e : topCenter->borders){
        //    getGraphics().beginPath().setFillStyle(phantom::Colors::BLACK)
        //        .line(*e->v0->point,*e->v1->point)
        //        .fill();
        //}
    }
}
