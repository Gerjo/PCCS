#include "Enemy.h"
#include "layer/EntityLayer.h"

namespace phantom{
    Enemy::Enemy() :
        _isMouseHover(false),
        _doRedraw(true)
    {
        setType("Enemy");

        _boundingBox.size.x = 10;
        _boundingBox.size.y = 10;
        _canHover           = true;
    }

    void Enemy::draw(){
        _doRedraw = false;

        getGraphics()
            .clear()
            .beginPath()
            .setFillStyle(Colors::BLUE)
            .rect(0, 0, _boundingBox.size.x, _boundingBox.size.y)
            .stroke();

        if(_isMouseHover) {
            const float size = 10;

            getGraphics()
                .beginPath()
                .setFillStyle(Colors::RED)
                .rect(-size, -size, _boundingBox.size.x + size * 2, _boundingBox.size.y + size * 2, false)
                .stroke();
        }
    }

    void Enemy::update(const float& elapsed){
        if(_doRedraw) {
            draw();
        }

        if(_isMouseHover) {
            _doRedraw = true;
        }

        _isMouseHover = false;
    }

    void Enemy::onCollision(Composite* other){

    }

    void Enemy::onMouseHover(const Vector3& mouseLocationWorld, const Vector3& mouseLocationScreen) {
        _isMouseHover = true;
        _doRedraw = true;
    }
}