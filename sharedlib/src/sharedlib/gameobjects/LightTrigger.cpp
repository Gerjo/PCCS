#include "LightTrigger.h"

LightTrigger::LightTrigger(): _subscribers(){
    Box3* b = new Box3(100,100,50,50);
    _boundingBox = *b;

    setType("LightTrigger");
}

LightTrigger::~LightTrigger() {
}

void LightTrigger::onCollision(Entity* other){
    if(other->isType("Soldier")){
        onTrigger();
    }
}

void LightTrigger::onTrigger(){
    _commandQueue.run();
}

void LightTrigger::update(const Time& time){
    GameObject::update(time);
}

void LightTrigger::subscribe(Composite* subscriber){
    _subscribers.push_back(subscriber);
}

void LightTrigger::subscribe(CommandQueue::Command command){
    _commandQueue.add(command);
}

vector<Composite*> LightTrigger::getSubscribers(){
    return _subscribers;
}

 