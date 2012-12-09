#include "Squad.h"
#include "../pathfinding/Pathfinding.h"
#include "../pathfinding/RouteDetails.h"

vector<Squad*> Squad::createSquads(vector<GameObject*> gameobjects, const Vector3& target, const float& distanceToLeader) {
    vector<RouteDetails> routes;

    Pathfinding* pathfinding = static_cast<BSPTree*>(gameobjects.front()->getLayer())->pathfinding;

    // Gather pathfinding details for each soldier:
    for(GameObject* gameobject : gameobjects) {
        Entity* entity = static_cast<Entity*>(gameobject);
        routes.push_back(pathfinding->getPathDetailled(entity, target));
    }

    // Sort low to high. RouteDetails implements an overload for this.
    std::sort(routes.begin(), routes.end());

    vector<Squad*> squads;

    // Build squads:
    for(RouteDetails& route : routes) {
        GameObject* gameobject = static_cast<GameObject*>(route.entity);

        if(!squads.empty() && squads.back()->getLeader()->distanceToSq(route.entity) < distanceToLeader) {
            squads.back()->addMember(gameobject);

        } else {
            // Create a new squad! Squads will be added to the game, hence a
            // pointer is used.
            squads.push_back(new Squad(gameobject));
        }
    }

    return squads;
}