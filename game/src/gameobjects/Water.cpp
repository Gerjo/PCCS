#include "Water.h"

Water::Water() : phantom::Entity()
{
    draw();
}

Water::~Water()
{
}

void Water::draw() {
    phantom::Graphics *gfx = getGraphics();
    gfx->beginPath();
    gfx->setFillStyle(phantom::Color(0, 0, 127, 127));
    gfx->rect(0, 0, 100, 100);
    gfx->beginPath();
}

void Water::update(float elapsed) {
    Entity::update(elapsed);
}