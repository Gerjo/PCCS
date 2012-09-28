#include "Tree.h"

Tree::Tree() : phantom::Entity()
{
    draw();
}

Tree::~Tree()
{
}

void Tree::draw() {
    phantom::Graphics *gfx = getGraphics();
    gfx->beginPath();
    gfx->setFillStyle(phantom::Color(75, 33, 0, 127));
    gfx->rect(0, 0, 30, 100);
    gfx->beginPath();
}

void Tree::update(float elapsed) {
    Entity::update(elapsed);
}