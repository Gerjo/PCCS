#include "Water.h"

Water::Water() : Entity() {
    draw();
}

Water::~Water() {

}

void Water::draw() {
    Graphics& gfx = getGraphics();
    gfx.beginPath();
    gfx.setFillStyle(phantom::Color(0, 0, 127, 127));
    gfx.image("images/Water 80x80.png", 0, 0, 80, 80);
    gfx.beginPath();
}

void Water::update(float elapsed) {
    Entity::update(elapsed);
}