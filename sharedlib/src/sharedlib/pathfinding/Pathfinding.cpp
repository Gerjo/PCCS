#include "Pathfinding.h"
#include "sharedlib/services/Services.h"

Pathfinding::Pathfinding(BSPTree& layer) : _layer(layer), _showDebug(false), _showBasicDebug(false) {
    _showDebug = false;
    _showBasicDebug = true;
    _visualize = false;
}

Pathfinding::Route Pathfinding::getPath(Entity* entity, const Vector3& goal) {
    stringstream prettyInfo;

    Vector3 start = entity->getPosition();

    double a  = phantom::Util::getTime();
    _layer.cleanPathfinding();

    Route route;

    if(_showDebug) {
        cout << endl<< endl<< endl<< endl;
    }

    if(_visualize) {
        getGraphics().clear();
    }

    // Goal space uses a "strict" heuristic. EG: we don't want to walk into a tree.
    Space* goalSpace  = _layer.getSpaceAtUsingHeuristic(goal, entity);

    // There is no "space" available at the destination. The entity probably wants
    // to walk into a tree. Returns an empty route.
    if(goalSpace == nullptr) {
        if(_showDebug) {
            cout << "Goal vector is not a space." << endl;
        }
        return route;
    }

    // Start space, first try using a strict heuristic. EG: If we start near a tree
    // we don't want to walk into that tree.
    Space* startSpace = _layer.getSpaceAtUsingHeuristic(start, entity);

    // Ok, did we find a start space with the strict heuristic? If not, it probably
    // means that our entity is stuck in a tree. Proceed with a less strict
    // heuristic. In most cases this will let the entity "leave" the solid object
    // that it's currently stuck on.
    if(startSpace == nullptr) {
        startSpace = _layer.getSpaceAtUsingHeuristic(start);
    }

    // Ok, we really can't walk anywhere. This is a rather odd case. Most likely
    // the user tried to walk outside of the BSP tree, or you've just found a bug
    // in the BSP tree.
    if(startSpace == nullptr) {
        if(_showDebug) {
            cout << "Start vector is not a space." << endl;
        }
        route.push_back(Vector3(goal));
        return route;
    }

    if(_showDebug) {
        cout << "Starting at: " << startSpace->getArea().toString();
        cout << "Ending at  : " << goalSpace->getArea().toString();
    }

    if(_visualize) {
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

        if(_visualize) {
            //cout << "  - Testing: " << current->getArea().toString();
            drawRect(current, Color(0, 127, 127, 10));
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
                testing->astarParent  = current;
                testing->isInOpenList = true;
                testing->g = current->g + Services::settings()->pathfinding_g_cost;
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

RouteDetails Pathfinding::getPathDetailled(Entity* entity, const Vector3& goal) {
    Route route = getPath(entity, goal);

    Vector3 position = entity->getPosition();
    Vector3* last    = &position;
    float lengthSq   = 0;

    // Chain all the distances together:
    for(auto it = route.begin(); it != route.end(); ++it) {
        lengthSq += (*it).distanceToSq(*last);
        last      = &(*it);
    }

    return RouteDetails(entity, route, lengthSq);
}


