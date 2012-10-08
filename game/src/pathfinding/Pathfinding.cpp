#include "Pathfinding.h"
#include "../Game.h"

Pathfinding::Pathfinding(EntityLayer& layer) :
    _layer(layer)
{
    _root = new Space(0.0f, 0.0f, 4000, 2000, 20.0f);
    cout << "BSP tree created. " << endl;

}

void Pathfinding::update(const float& elapsed) {
    _root->clear();

    vector<Composite*>& entities = _layer.getComponents();
    vector<Composite*>::iterator it = entities.begin();

    // Insert everything to build up the BSP tree.
    for(;it != entities.end(); ++it) {
        Entity* entity = static_cast<Entity*>(*it);
        _root->insert(entity);
    }

    Camera& cam       = static_cast<Game*>(getGame())->getRtsCamera().getPhantomCamera();
    MouseState* mouse = getDriver()->getInput()->getMouseState();
    Vector3 pos       = cam.getWorldCoordinates(mouse->getMousePosition());

    Vector3 start(0, 0, 0);

    Space* clickSpace = _root->findSpace(pos);
    Space* goalSpace  = _root->findSpace(start);


    if(clickSpace != 0) {
        goalSpace->markBlack();
        clickSpace->markBlack();

        priority_queue<Space*, vector<Space*>, CompareShapesAstar> open;

        clickSpace->isInOpenList = true;
        open.push(clickSpace);

        bool isRunning = true;
        int timeout    = 0;

        while(isRunning) {
            if(open.empty() || timeout++ > 1000) {
                cout << "Cannot find route. " << endl;
                break;
            }

            //cout << "Popping head." << endl;
            Space* current = open.top();
            open.pop();

            if(current == goalSpace) {
                Space* step = clickSpace;

                while(step != 0 && step != goalSpace) {
                   //cout << "retracing steps! " << step->getArea().toString();
                    step->markBlack();

                    if(step == step->astarParent) {
                        //cout << " breaking loop, recursion found. " << endl;
                        break;
                    }

                    step = step->astarParent;
                }

                //cout << "The end has been reached! Whoop!" << endl;
                break;
            }

            current->isVisited = true;

            vector<Space*>& neighbours = _root->findNeighbours(current);

            for(size_t i = 0; i < neighbours.size(); ++i) {
                Space* testing = neighbours[i];
                testing->astarParent = current;
                if(!testing->isInOpenList) {
                    testing->isInOpenList = true;
                    testing->g = 0;//current->g + 1;
                    testing->h = calculateHeuristic(goalSpace, testing);
                    testing->h = testing->h * testing->h;
                    open.push(testing);
                }
            }
        }
    }

    getGraphics()
            .clear()
            .beginPath()
            .setFillStyle(Colors::BROWN)
            .rect(0, 0, 4000, 2000)
            .fill();

    _root->render(getGraphics());

}

float Pathfinding::calculateHeuristic(Space* goal, Space* testing) {
    Box3& goalArea    = goal->getArea();
    Box3& testingArea = testing->getArea();

    return
           abs(goalArea.origin.x - testingArea.origin.x)
            +
           abs(goalArea.origin.y - testingArea.origin.y);
}