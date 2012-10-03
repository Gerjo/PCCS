#include "Tank.h"

Tank::Tank() : phantom::Entity() {
    draw();
}

Tank::~Tank() {
}

void Tank::draw() {
    Graphics& gfx = getGraphics();
    gfx.beginPath();
    gfx.setFillStyle(phantom::Color(127, 127, 127, 127));
    gfx.image("images/Tank Bot.png", 0, 140, 281, 335);
    gfx.image("images/Tank Barrel.png", 17, 0, 246, 479);
    gfx.beginPath();
}

void Tank::update(float elapsed) {
    Entity::update(elapsed);
}