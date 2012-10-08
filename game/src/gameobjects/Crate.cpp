#include "Crate.h"

namespace phantom{
    Crate::Crate():isVisible(true){
        setType("Crate");
        draw();
        setX(100);
        setY(100);
    }
    void Crate::draw(){
        getGraphics().clear();
        if(isVisible){
            getGraphics()
                .beginPath()
                .rect(-1,-1, 14,14)
                .setFillStyle(Colors::BLACK)
                .stroke();
            getGraphics()
                .beginPath()
                .rect(0,0,12,12)
                .setFillStyle(Colors::HOTPINK)
                .stroke();
        }
    }
    void Crate::onCollision(Composite* other){
        if(other->isType("Soldier") && isVisible){
            std::cout << "Got an item!!" << endl;
            isVisible = false;
            draw();
        }
    }

}