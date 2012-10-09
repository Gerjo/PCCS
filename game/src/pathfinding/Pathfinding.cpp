#include "Pathfinding.h"
#include "../Game.h"

Pathfinding::Pathfinding(BSPTree& layer) : _layer(layer), _showDebug(false) {
    _showDebug = true;
}

deque<Space*> Pathfinding::getPath(Vector3& start, Vector3& goal) {

    if(_showDebug)
        cout << "getPath entry point." << endl;

    Space* goalSpace  = _layer.getSpaceAt(goal);
    Space* startSpace = _layer.getSpaceAt(start);

    priority_queue<Space*, vector<Space*>, CompareShapesAstar> open;

    drawRect(goalSpace, Colors::BLACK);
    drawRect(startSpace, Colors::BLACK);

    startSpace->isInOpenList = true;
    open.push(startSpace);

    deque<Space*> route;

    while(true) {
        if(open.empty()) {
            if(_showDebug)
                cout << "Open list empty." << endl;
            break;
        }

        Space* current = open.top();
        open.pop();

        if(current == goalSpace) {
            unfoldRoute(route, current, startSpace);
            route.push_front(goalSpace);
        }

        vector<Space*>& neighbours = _layer.getNeighbours(current);

        for(size_t i = 0; i < neighbours.size(); ++i) {
            Space* testing = neighbours[i];

            testing->astarParent = current;
            if(!testing->isInOpenList) {
                testing->isInOpenList = true;
                testing->g = current->g + 1;
                testing->h = calculateHeuristic(goalSpace, testing);
                testing->h = testing->h * testing->h;
                open.push(testing);
            }
        }
    }

    return route;
}

void Pathfinding::update(const float& elapsed) {

    getGraphics().clear();

    Camera& cam       = static_cast<Game*>(getGame())->getRtsCamera().getPhantomCamera();
    MouseState* mouse = getDriver()->getInput()->getMouseState();
    Vector3 start     = cam.getWorldCoordinates(mouse->getMousePosition());
    Vector3 goal(0, 0, 0);

    if(mouse->isButtonDown(Buttons::LEFT_MOUSE) && _layer.getSpaceAt(start) != 0) {
        _somePath = getPath(start, goal);
    }

    getGraphics().beginPath().setLineStyle(Colors::RED);

    if(_somePath.size() > 1) {
        Vector3 prev = _somePath.front()->getCenter();
        for(size_t i = 1; i < _somePath.size(); ++i) {
            Vector3 center = _somePath[i]->getCenter();

            getGraphics().line(prev.x, prev.y, center.x, center.y).stroke();

            prev = center;

            getGraphics().beginPath().setLineStyle(Colors::BLACK);
            //if(i == 2) break;
        }
        getGraphics().stroke();
    }
}

void Pathfinding::drawRect(Box3& area, Color color) {
    getGraphics()
        .beginPath()
        .setFillStyle(color)
        .rect(area.origin.x, area.origin.y, area.size.x, area.size.y)
        .fill();
}

void Pathfinding::drawRect(Space* whom, Color color) {
    drawRect(whom->getArea(), color);
}

float Pathfinding::calculateHeuristic(Space* goal, Space* testing) {
    Box3& goalArea    = goal->getArea();
    Box3& testingArea = testing->getArea();

    return
           abs(goalArea.origin.x - testingArea.origin.x)
            +
           abs(goalArea.origin.y - testingArea.origin.y);
}

void Pathfinding::unfoldRoute(deque<Space*>& out, Space* unfoldee, Space* end) {

    // NB: We're using a single-linked-list, so must retrace steps.
    Space* step = end;

    int timeout = 0;

    if(_showDebug) {
        cout << "Unfold: " << unfoldee->getArea().toString();
        cout << "End:    " << end->getArea().toString();
    }

    while(true) {
        if(step == step->astarParent) {
            if(_showDebug) cout << " breaking loop, recursion found. " << endl;
            break;
        }

        out.push_front(step);

        // *hack* -- Gerjo
        if(step->astarParent != 0 && step->astarParent->astarParent == step) {
            out.push_front(step->astarParent);
            if(_showDebug) cout << "Recursion found. My parent's parent points to me." << endl;
            break;
        }

        if(++timeout > 10000) {
            if(_showDebug)
                cout << "Cancelled unfolding. Iterations so far: " << timeout
                    << ". You probably have recursion? Or a too big map." << endl;
            break;
        }

        if(step->astarParent == 0) {
            if(_showDebug)
                cout << "Breaking, this space leads to NULL." << step->getArea().toString();
            break;
        }

        step = step->astarParent;
    }

    if(_showDebug)
        cout << "End of unfolding method." << endl;
}
