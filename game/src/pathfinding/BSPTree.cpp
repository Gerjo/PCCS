#include "BSPTree.h"

BSPTree::BSPTree(float initialWidth, float initialHeight, float smallestSize, unsigned int collisionMaxPerSpace) :
    _enableDebug(false),
    _initialWidth(initialWidth),
    _initialHeight(initialHeight),
    _smallestSize(smallestSize),
    _collisionMaxPerSpace(collisionMaxPerSpace)
{
    _boundingBox.size.x = _initialWidth;
    _boundingBox.size.y = _initialHeight;

    _root = new Space(0, 0, _initialWidth, _initialHeight, smallestSize);

    stringstream ss1;
    ss1 << "Created a " << _initialWidth << "x" << _initialHeight << " BSP tree." << endl;
    Console::log(ss1.str());

    stringstream ss2;
    ss2 << "Minimal tile size: " << smallestSize << "x" << smallestSize
            << ". Preferred collisions per space: " << collisionMaxPerSpace << endl;
    Console::log(ss2.str());
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
    _root->clear();
    Layer::update(elapsed);
    getGraphics().clear();

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

        //getGraphics().beginPath();
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
    return _root->getSpaceAt(location);
}

vector<Space*>& BSPTree::getNeighbours(Space* location) {
    return _root->getNeighboursOf(location);
}

void BSPTree::cleanPathfinding() {
    _root->cleanPathfinding();
}

void BSPTree::getEntitiesAt(vector<Entity*>& out, Vector3& location) {
    Space* space = _root->getSpaceAt(location);

    if(space != 0) {
        vector<Entity*>& entities = space->getEntities();

        for(size_t i = 0; i < entities.size(); ++i) {
            if(entities[i]->getBoundingBox().contains(location)) {
                out.push_back(entities[i]);
            }
        }
    }
}