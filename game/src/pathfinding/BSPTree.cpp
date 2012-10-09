#include "BSPTree.h"

BSPTree::BSPTree(float initialWidth, float initialHeight, float smallestSize, unsigned int collisionMaxPerSpace) :
    _enableDebug(false),
    _initialWidth(initialWidth),
    _initialHeight(initialHeight),
    _smallestSize(smallestSize),
    _collisionMaxPerSpace(collisionMaxPerSpace)
{

    _root = new Space(0, 0, _initialWidth, _initialHeight, smallestSize);
     cout << "BSP tree, construction completed." << endl;
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

    _root->clear();

    vector<Composite*>& children    = getComponents();
    vector<Composite*>::iterator it = children.begin();

    // Insert everything to build up the BSP tree.
    for(;it != children.end(); ++it) {
        Entity* entity = static_cast<Entity*>(*it);
        _root->insert(entity);
    }

    vector<Space*> spaces;
    _root->getCollisionSpaces(spaces, _collisionMaxPerSpace);

    for(size_t i = 0; i < spaces.size(); ++i) {
        Box3& area = spaces[i]->getArea();
        vector<Entity*>& entities = spaces[i]->getEntities();
        vector<Entity*>::iterator a, b;
        int offset = 0;

        for(a = entities.begin(); a != entities.end(); ++a, ++offset) {
            b = entities.begin();
            std::advance(b, offset);
            for(; b != entities.end(); ++b) {
                if(*a != *b) {
                    if(calculateCollision(*a, *b)) {
                        //if((*a)->canCollideWith(*b)) { // <-- actually costs FPS ?!?!
                            (*a)->onCollision(*b);
                            (*b)->onCollision(*a);
                        //}
                    }
                }
            }
        }

        //cout << "Collision space with: " << spaces[i]->getEntities().size() << endl;

        //getGraphics().setFillStyle(Colors::GREEN);
        //getGraphics().rect(area.origin.x, area.origin.y, area.size.x, area.size.y);
        //getGraphics().fill();
    }

    if(_enableDebug) {
        _root->render(getGraphics());
    }
}

bool BSPTree::calculateCollision(Entity* a, Entity* b) {
    // TODO: fancier shape testing, please!
    return a->getBoundingBox().intersect(b->getBoundingBox());;
}

void BSPTree::enableDebug() {
    _enableDebug = true;
}
void BSPTree::disableDebug() {
    _enableDebug = false;
}

Space* BSPTree::getSpaceAt(Vector3& location) {
    Space* loot = _root;
    cout << "getSpaceAt." << endl;
    cout << &_root << endl;
    cout << "donut" << endl;
    return 0;//_root->findSpace(location);
}

vector<Space*>& BSPTree::getNeighbours(Space* location) {
    return _root->findNeighbours(location);
}