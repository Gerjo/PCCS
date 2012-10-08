#include "BSPTree.h"

BSPTree::BSPTree(float initialWidth, float initialHeight, float smallestSize) :
    _enableDebug(false),
    _initialWidth(initialWidth),
    _initialHeight(initialHeight),
    _smallestSize(smallestSize)
{

    _root = new Space(0, 0, _initialWidth, _initialHeight, smallestSize);
}

BSPTree::~BSPTree() {
    delete _root;
}

void BSPTree::addComponent(Composite* component) {
    if(dynamic_cast<Entity*>(component) == 0) {
        throw GameException(
                "Only phantom::Entity derivatives "
                "can be added to an BSP layer."
        );
    }

    Layer::addComponent(component);
}

void BSPTree::update(const float& elapsed) {
    Layer::update(elapsed);

    // TODO remove:
    Graphics& g = getGraphics()
        .clear()
        .beginPath()
        .setFillStyle(Colors::BROWN)
        .rect(0, 0, _initialWidth, _initialHeight)
        .fill();

    _root->clear();

    vector<Composite*>& children    = getComponents();
    vector<Composite*>::iterator it = children.begin();

    // Insert everything to build up the BSP tree.
    for(;it != children.end(); ++it) {
        Entity* entity = static_cast<Entity*>(*it);
        _root->insert(entity);
    }

    if(_enableDebug) {
        _root->render(g);
    }
}

void BSPTree::enableDebug() {
    _enableDebug = true;
}
void BSPTree::disableDebug() {
    _enableDebug = false;
}

Space* BSPTree::getSpaceAt(Vector3& location) {
    return _root->findSpace(location);
}

vector<Space*>& BSPTree::getNeighbours(Space* location) {
    return _root->findNeighbours(location);
}