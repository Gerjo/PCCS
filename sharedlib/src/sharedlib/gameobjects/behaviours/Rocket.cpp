#include "Rocket.h"

Rocket::Rocket(){
    _position = Vector3(0,0);
    _velocity = Vector3(0,0);
    _creationTime = 0;
    _ttl = 1;
    _typeName = "Rocket";
}

void Rocket::onDestroy(Graphics* graphics){
    (*graphics)
        .clear()
        .beginPath()
        .setFillStyle(Colors::WHITE)
        .image("images/projectiles/tree.png", 0, 0, 64, 64)
        .rotate(_direction.getAngleXOY() + 90.0f)
        .stroke()
        ;
}

void Rocket::render(Graphics* graphics){
    (*graphics)
        .clear()
        .beginPath()
        .setFillStyle(Colors::WHITE)
        .image("images/projectiles/rocket.png", 0, 0, 11, 33)
        .rotate(_direction.getAngleXOY() + 90.0f)
        .stroke()
        ;
}