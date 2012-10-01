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
    gfx->image("Water 80x80.png", 0, 0, 80, 80);
    gfx->beginPath();
}

void Water::update(float elapsed) {
    Entity::update(elapsed);
}