#include "Pathfinding.h"
#include "src/Game.h"

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

    for(;it != entities.end(); ++it) {
        Entity* entity = static_cast<Entity*>(*it);
        _root->insert(entity);
    }

    Game* game = static_cast<Game*>(getGame());
    Camera& cam = game->getRtsCamera().getPhantomCamera();

    MouseState* mouse = getDriver()->getInput()->getMouseState();
    Vector3 pos = cam.getWorldCoordinates(mouse->getMousePosition());

    double time = phantom::Util::getTime();
    Space* leaf = _root->findLeaf(pos);
    double diff = phantom::Util::getTime() - time;

    if(leaf != 0) {
        printf("lookup took: %f\n", diff);
        leaf->mark();
    }

    getGraphics()
            .clear()
            .beginPath()
            .setFillStyle(Colors::BROWN)
            .rect(0, 0, 4000, 2000)
            .fill();

    _root->render(getGraphics());

}