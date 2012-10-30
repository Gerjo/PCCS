#include "BSPTree.h"
#include "Pathfinding.h"

BSPTree::BSPTree(float initialWidth, float initialHeight, float smallestSize, unsigned int collisionMaxPerSpace) :
    _enableDebug(false),
    _initialWidth(initialWidth),
    _initialHeight(initialHeight),
    _smallestSize(smallestSize),
    _collisionMaxPerSpace(collisionMaxPerSpace),
    _isTreeIterating(false)
{
    setType("BSPTree");
    _boundingBox.size.x = _initialWidth;
    _boundingBox.size.y = _initialHeight;

    _root = new Space(0, 0, _initialWidth, _initialHeight, smallestSize);

    stringstream ss1;
    ss1 << "Created a " << _initialWidth << "x" << _initialHeight << " BSP tree.";
    //Console::log(ss1.str());

    stringstream ss2;
    ss2 << "Minimal tile size: " << smallestSize << "x" << smallestSize
            << ". Preferred collisions per space: " << collisionMaxPerSpace;
    //Console::log(ss2.str());

    pathfinding = new Pathfinding(*this);
}

BSPTree::~BSPTree() {
    delete _root;
    delete pathfinding;
}

void BSPTree::addComponent(Composite* component) {
    if(dynamic_cast<Entity*>(component) == 0) {
        throw SharedException(
                "Only phantom::Entity derivatives "
                "can be added to a BSPtree layer."
        );
    }

    Layer::addComponent(component);
}

void BSPTree::update(const Time& time) {
    pathfinding->update(time);

    _isTreeIterating = true;
    _root->clear();
    Layer::update(time);

    getGraphics().clear();

    vector<Composite*>& children    = getComponents();

    // Insert everything to build up the BSP tree.
    for(vector<Composite*>::iterator it = children.begin(); it != children.end(); ++it) {
        Entity* entity = static_cast<Entity*>(*it);
        
        _root->insert(entity);
    }

    _isTreeIterating = false;
    return;

    vector<Space*> spaces;
    _root->getCollisionSpaces(spaces, _collisionMaxPerSpace);

    for(size_t i = 0; i < spaces.size(); ++i) {
        Box3& area = spaces[i]->getArea();
        vector<Entity*>& entities = spaces[i]->getEntities();
        vector<Entity*>::iterator a, b;
        int offset = 0;

        for(a = entities.begin(); a != entities.end(); ++a, ++offset) {
            if((*a)->isDestroyed()) {
                continue;
            }

            b = entities.begin();
            std::advance(b, offset);
            for(; b != entities.end(); ++b) {
                if((*b)->isDestroyed()) {
                    continue;
                }

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



    for(auto it = _destroyUs.begin(); it != _destroyUs.end(); ++it) {
        cout << "Delayed destruction of: " << (*it)->getType() << endl;
        destroyComponent(*it);
    }
    _destroyUs.clear();


    for(auto it = _removeUs.begin(); it != _removeUs.end(); ++it) {
        cout << "Delayed removal of: " << (*it)->getType() << endl;
        removeComponent(*it);
    }
    _removeUs.clear();

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

void BSPTree::destroyComponent(Composite* who) {
    if(_isTreeIterating) {
        _destroyUs.push_back(who);
    } else {
        Layer::destroyComponent(who);
    }
}

void BSPTree::removeComponent(Composite* who) {
    if(_isTreeIterating) {
        _removeUs.push_back(who);
    } else {
        Layer::removeComponent(who);
    }
}