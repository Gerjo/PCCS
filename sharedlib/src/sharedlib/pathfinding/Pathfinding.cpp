#include "Pathfinding.h"

Pathfinding::Pathfinding(BSPTree& layer) : _layer(layer), _showDebug(false), _showBasicDebug(false) {
    _showDebug = false;
    _showBasicDebug = true;
}

Pathfinding::Route Pathfinding::getPath(Entity* entity, Vector3& goal) {
    stringstream prettyInfo;

    Vector3 start = entity->getPosition();

    double a  = phantom::Util::getTime();
    _layer.cleanPathfinding();

    Route route;

    if(_showDebug) {
        getGraphics().clear();
        cout << endl<< endl<< endl<< endl;
    }

    Space* goalSpace  = _layer.getSpaceAtUsingHeuristic(goal, entity);
    Space* startSpace = _layer.getSpaceAtUsingHeuristic(start);

    if(goalSpace == 0) {
        if(_showDebug) {
            cout << "Goal vector is not a space." << endl;
        }

        return route;
    }

    if(startSpace == 0) {
        if(_showDebug) {
            cout << "Start vector is not a space." << endl;
        }

        return route;
    }

    if(_showDebug) {
        cout << "Starting at: " << startSpace->getArea().toString();
        cout << "Ending at  : " << goalSpace->getArea().toString();

        Box3& m = startSpace->getArea();

        getGraphics().beginPath().setFillStyle(Color(0, 0, 127, 20))
                .rect(m.origin.x+4, m.origin.y+4, m.size.x-8, m.size.y-8)
                .fill();

        Box3& n = goalSpace->getArea();
        getGraphics().beginPath().setFillStyle(Color(0, 0, 127, 20))
               .rect(n.origin.x+4, n.origin.y+4, n.size.x-8, n.size.y-8)
               .fill();
    }

    priority_queue<Space*, vector<Space*>, CompareShapesAstar> open;

    startSpace->isInOpenList = true;
    open.push(startSpace);

    if(_showBasicDebug) {
        prettyInfo << "Pathfinding overhead: " << std::fixed << (phantom::Util::getTime() - a) << " seconds. ";
    }

    int spacesScanned = 0;
    const double startTime  = phantom::Util::getTime();


    int timeout = 0;
    while(true) {
        if(open.empty()) {
            if(_showBasicDebug || _showDebug) {
                cout << "      Open list empty." << endl;
                double now = phantom::Util::getTime();

                if(_showBasicDebug) {
                    prettyInfo << "No route found, scanned "<< spacesScanned << " Tile(s) in " << std::fixed << (now - startTime) << " seconds.";
                }

            }

            break;
        }

        if(timeout++ > 10000) {
            cout << "      I give up after " << timeout << " tries. " << endl;
            double now = phantom::Util::getTime();
            cout << "A* scanned " << spacesScanned << " Tile(s) in " << std::fixed << (now - startTime) << " seconds. " << endl;

            break;
        }

        Space* current = open.top();
        open.pop();

        if(_showDebug) {
            //cout << "  - Testing: " << current->getArea().toString();

            drawRect(current, Color(0, 127, 127, 5));
        }

        if(current == goalSpace) {
            if(_showDebug) {
                cout << "    **** found! This is a good sign. " << endl;
            }
            unfoldRoute(route, current, startSpace, entity);


            if(!route.empty()) {
                route.pop_front();

                Vector3 lastpos = goal - entity->getBoundingBox().size * 0.5;

                // Replace the last way-point with our mouse click coordinates:
                if(route.empty()) {
                    route.push_back(lastpos);
                } else {
                    route.back() = lastpos;
                }
            }


            double now = phantom::Util::getTime();

            if(_showBasicDebug) {
                prettyInfo << "Found route, A* scanned " << spacesScanned << " Tile(s) in " << std::fixed << (now - startTime) << " seconds. Waypoint(s): " << route.size() << ".";
            }

            break;
        }

        vector<Space*>& neighbours = _layer.getNeighbours(current, entity);

        if(_showDebug && neighbours.empty()) {
            cout << "      No neighbours found." << endl;
        }

        for(size_t i = 0; i < neighbours.size(); ++i) {
            Space* testing = neighbours[i];

            if(!testing->isInOpenList) {
                spacesScanned++;
                testing->astarParent = current; // kind of experimental.
                testing->isInOpenList = true;
                testing->g = current->g + 1;
                testing->h = calculateHeuristic(goalSpace, testing);
                testing->h = testing->h * testing->h;
                open.push(testing);
            }
        }
    }

    if(_showBasicDebug) {
        //cout << prettyInfo.str() << endl;
        Console::log(prettyInfo.str());
    }

    return route;
}

void Pathfinding::drawRect(Box3& area, Color color) {
    getGraphics()
        .beginPath()
        .setFillStyle(color)
        .rect(area.origin.x + 1, area.origin.y + 1, area.size.x - 2, area.size.y - 2)
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

void Pathfinding::unfoldRoute(Route& out, Space* unfoldee, Space* end, Entity* entity) {

    // NB: We're using a single-linked-list, so must retrace steps.
    Space* step = unfoldee;

    int timeout = 0;

    Vector3 halfSize = entity->getBoundingBox().size * 0.5;

    if(_showDebug) {
        cout << "Unfold: " << unfoldee->getArea().toString();
        cout << "End:    " << end->getArea().toString();
    }

    while(true) {
        if(step == step->astarParent) {
            if(_showDebug) cout << " breaking loop, recursion found. " << endl;
            break;
        }

        out.push_front(step->getCenter() - halfSize);

        if(++timeout > 10000) {
            if(_showDebug)
                cout << "Canceled unfolding. Iterations so far: " << timeout
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
