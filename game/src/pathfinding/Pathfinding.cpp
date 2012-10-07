#include "Pathfinding.h"

Pathfinding::Pathfinding(EntityLayer& layer) :
    _layer(layer)
{
    _root = new Space(0.0f, 0.0f, 2000, 1000, 20.0f);
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

    getGraphics()
            .clear()
            .beginPath()
            .setFillStyle(Colors::BROWN)
            .rect(0, 0, 2000, 1000)
            .fill()
            ;

    _root->render(getGraphics());



}