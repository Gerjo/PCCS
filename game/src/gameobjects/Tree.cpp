#include "Tree.h"

Tree::Tree() : GameObject() {
    _boundingBox.size.x = 64;
    _boundingBox.size.y = 64;

    getGraphics()
        .beginPath()
        .setFillStyle(Colors::WHITE)
        .image("images/tree64.png", 0, 0, _boundingBox.size.x, _boundingBox.size.y)
        .fill()
    ;
}