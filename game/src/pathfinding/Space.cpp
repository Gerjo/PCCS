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

    //if(_left == 0) {
        entities.push_back(entity);
    //}

    if(!isLeaf()) {
        if(_left->contains(entity)) {
            _left->insert(entity);
        }

        if(_right->contains(entity)) {
            _right->insert(entity);
        }
    }
}

void Space::clear() {
    entities.clear();
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
    if(entities.empty() || isLeaf()) {
        g.beginPath();

        if(entities.size() > 0) {
            g.setFillStyle(Color(127, 0, 0, 60));
        } else {
            g.setFillStyle(Color(127, 127, 127, 20));
        }

        g.rect(
            _area.origin.x + 1,
            _area.origin.y + 1,
            _area.size.x - 2,
            _area.size.y - 2
        );

        g.fill();

        g.beginPath();
        g.setFillStyle(Colors::BLACK);
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