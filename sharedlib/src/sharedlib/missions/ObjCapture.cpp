#include "ObjCapture.h"
#include <core/Composite.h>
#include <core/PhantomGame.h>
#include <utils/Time.h>

ObjCapture::ObjCapture(phantom::Box3 poi, string title): Objective(title), _poi(poi), timer(5){
    ttl = -1;
    isCapturing = false;
    _boundingBox = _poi;
    setType(title);
    repaint();
}

ObjCapture::~ObjCapture(){
}


void ObjCapture::setConditions(){
    ttl = 10;
    isCapturing = true;
}

void ObjCapture::onCollision(Composite* entity){
    if(entity->isType("Soldier")){
        if(!isCapturing){
            cout << "capturing!" << endl;
            setConditions();
        }
    }
}
void ObjCapture::update(const PhantomTime& time){
    GameObject::update(time);
    if(ttl >= 0){
        ttl -= time.getElapsed();
    }

}
void ObjCapture::paint(){
    getGraphics()
        .clear()
        .beginPath()
        .setFillStyle(Colors::WHITE)
        .rect(_poi)
        .fill()
        .stroke()
        ;
}

bool ObjCapture::conditionsMet(){
    if(ttl <= 0 && isCapturing){
        cout << "objective complete" << endl;
        return true;
    }
    return false;
}