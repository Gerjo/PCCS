#include "Trigger.h"

Trigger::Trigger(): _subscribers(){
    Box3* b = new Box3(100,100,50,50);
    _boundingBox = *b;
    setType("Trigger");
}
Trigger::~Trigger(){}

void Trigger::onCollision(Entity* other){
    if(other->isType("Soldier")){
        onTrigger();
    }
}
void Trigger::onTrigger(){
    _commandQueue.run();
}
void Trigger::update(const Time& time){
    GameObject::update(time);

    getGraphics()
        .clear()
        .beginPath()
        .setFillStyle(Colors::WHITE)
        .rect(_boundingBox)
        .fill()
        .stroke()
        ;
}
void Trigger::subscribe(Composite* subscriber){
    _subscribers.push_back(subscriber);
}
void Trigger::subscribe(CommandQueue::Command command){
    _commandQueue.add(command);
}
vector<Composite*> Trigger::getSubscribers(){
    return _subscribers;
}

 