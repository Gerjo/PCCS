#include "Tree.h"

Tree::Tree() : GameObject() {
    getGraphics()
        .beginPath()
        .setFillStyle(Colors::WHITE)
        .image("images/tree64.png", 0, 0, 64, 64)
        .fill()
    ;
}