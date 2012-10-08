#include "Enemy.h"
#include "layer/EntityLayer.h"

namespace phantom{
    Enemy::Enemy(){
        setType("Enemy");
        target = 0;
        draw();
        _boundingBox.size.x = 50;
        _boundingBox.size.y = 50;
    }
    void Enemy::draw(){
        getGraphics().clear();
        getGraphics()
            .beginPath()
            .setFillStyle(Colors::WHITE)
            .rect(-1.0f, -1.0f, 14.0f, 14.0f)
            .stroke();

        getGraphics()
            .beginPath()
            .rect(0,0, 12, 12);

        if(attack) {
            getGraphics().setFillStyle(Colors::BLACK);
        } else {
            getGraphics().setFillStyle(Colors::BLUE);
        }
        getGraphics().stroke();


    }
    void Enemy::update(const float& elapsed){
        draw();

        attack = false;
    }
    void Enemy::onCollision(Composite* other){
        if(target == 0){
            if(other->isType("Soldier")){
                attack = true;
                target = static_cast<Soldier*>(other);
            }
        }
    }
}