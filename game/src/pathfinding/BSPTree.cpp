#include "BSPTree.h"

BSPTree::BSPTree(float initialWidth, float initialHeight, float smallestSize) {
    _initialWidth  = initialWidth;
    _initialHeight = initialHeight;
    _smallestSize  = smallestSize;

    _root = new Space(0, 0, _initialWidth, _initialHeight, smallestSize);

    getGraphics()
        .beginPath()
        .setFillStyle(Colors::BROWN)
        .rect(0, 0, _initialWidth, _initialHeight)
        .fill()
    ;
}

BSPTree::~BSPTree() {
    delete _root;
}

void BSPTree::update(const float& elapsed) {
    Layer::update(elapsed);

    Graphics& g = getGraphics();
    g.clear()
    .beginPath()
    .setFillStyle(Colors::BROWN)
    .rect(0, 0, _initialWidth, _initialHeight)
    .fill();

    _root->clear();

    vector<Composite*>& children    = getComponents();
    vector<Composite*>::iterator it = children.begin();

    cout << " size: " << children.size() << endl;

    // Insert everything to build up the BSP tree.
    for(;it != children.end(); ++it) {
        Entity* entity = static_cast<Entity*>(*it);
        _root->insert(entity);
    }

    _root->render(g);
}