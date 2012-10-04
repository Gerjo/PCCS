#include "Tree.h"

Tree::Tree() : GameObject() {
    draw();
}

Tree::~Tree() {

}

void Tree::draw() {
    Graphics& gfx = getGraphics();
    gfx.beginPath();
    gfx.setFillStyle(phantom::Color(75, 33, 0, 127));
    gfx.image("images/tree.png", 0, 0, 151, 142);
    gfx.beginPath();
}

void Tree::update(float elapsed) {
    GameObject::update(elapsed);
}