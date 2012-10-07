#include "Space.h"

Space::Space(float x, float y, float width, float height, float smallestSize) {
    _area.origin.x  = x;
    _area.origin.y  = y;
    _area.size.x    = width;
    _area.size.y    = height;
    _smallestSize   = smallestSize;
    _left           = 0;
    _right          = 0;
    float scale     = 0.5f;
    _isBlack       = false;

    if(width > _smallestSize || height > _smallestSize) {
        float halfWidth  = width * scale;
        float halfHeight = height * scale;

        if(width > height) {
            _left  = new Space(x, y, halfWidth, height, _smallestSize);
            _right = new Space(x + halfWidth, y, halfWidth, height, _smallestSize);
        } else {
            _left  = new Space(x, y, width, halfHeight, _smallestSize);
            _right = new Space(x, y + halfHeight, width, halfHeight, _smallestSize);
        }
    }
}

void Space::insert(Entity* entity) {
    _entities.push_back(entity);

    if(!isLeaf()) {
        if(_left->contains(entity)) {
            _left->insert(entity);
        }

        if(_right->contains(entity)) {
            _right->insert(entity);
        }
    }
}

void Space::markEdge(Box3& area) {
    if(_area.intersect(area)) {
        if(_entities.empty()) {
            markPink();
        } else {
            if(!isLeaf()) {
                _left->markEdge(area);
                _right->markEdge(area);
            }
        }

    }
}

void Space::clear() {
    _entities.clear();
    _isBlack = false;
    _isPink = false;

    if(!isLeaf()) {
        _left->clear();
        _right->clear();
    }
}

bool Space::contains(Entity* entity) {
    return _area.intersect(entity->getBoundingBox());
    //return _area.contains(entity->getPosition());
}

void Space::render(Graphics& g) {
    if(_entities.empty() || isLeaf()) {
        g.beginPath();

        if(_entities.size() > 0) {
            g.setFillStyle(Color(127, 0, 0, 60));
        } else {
            g.setFillStyle(Color(127, 127, 127, 20));
        }

        if(_isBlack) {
            g.setFillStyle(Colors::BLACK);
        } else if(_isPink) {
            g.setFillStyle(Colors::HOTPINK);
        }

        g.rect(
            _area.origin.x + 1,
            _area.origin.y + 1,
            _area.size.x - 2,
            _area.size.y - 2
        );

        g.fill();

        g.beginPath();

        if(_isBlack) {
            g.setFillStyle(Colors::WHITE);
        } else {
            g.setFillStyle(Colors::BLACK);
        }

        g.rect(
            _area.origin.x + _area.size.x * 0.5f - 5,
            _area.origin.y + _area.size.y * 0.5f,
            10,
            1
        );

        g.rect(
            _area.origin.x + _area.size.x * 0.5f,
            _area.origin.y + _area.size.y * 0.5f - 5,
            1,
            10
        );

        g.fill();

        if(!isLeaf()) {
            return;
        }
    }

    if(!isLeaf()) {
        _left->render(g);
        _right->render(g);
    }
}

bool Space::isLeaf() {
    return _left == 0;
}

Space* Space::findLeaf(Vector3& v) {

    // First empty space, thus also a leaf:
    if(_area.contains(v) && _entities.empty()) {
        return this;
    }

    if(isLeaf()) {
        if(_area.contains(v)) {
            return this;
        } else {
            return 0;
        }
    }

    if(_left->getArea().contains(v)) {
        Space* left = _left->findLeaf(v);

        if(left != 0) {
            return left;
        }
    }

    return _right->findLeaf(v);
}

void Space::markBlack() {
    _isBlack = true;
}

void Space::markPink() {
    _isPink = true;
}

Box3& Space::getArea() {
    return _area;
}