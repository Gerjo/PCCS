#ifndef TRIGGER_H
#define TRIGGER_H

#include <phantom.h>
#include "../gameobjects/GameObject.h"
#include "../CompileConfig.h"
#include "../CommandQueue.h"
class LIBEXPORT Trigger : public GameObject{

public:
    Trigger();
    ~Trigger();

    void subscribe(phantom::Composite* subscriber);
    void subscribe(CommandQueue::Command command);
    virtual void update(const Time& time);
    virtual void onCollision(Entity* other);
    void onTrigger();
    vector<Composite*> getSubscribers();

private:
    vector<Composite*> _subscribers;
    CommandQueue _commandQueue;
};


#endif // TRIGGER_H