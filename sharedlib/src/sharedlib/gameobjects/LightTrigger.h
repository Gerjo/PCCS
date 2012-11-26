#ifndef LightTrigger_H
#define LightTrigger_H

#include <phantom.h>
#include "../gameobjects/GameObject.h"
#include "../CompileConfig.h"
#include "../CommandQueue.h"

class LIBEXPORT LightTrigger : public GameObject{
public:
    LightTrigger();
    ~LightTrigger();

    void subscribe(phantom::Composite* subscriber);
    void subscribe(CommandQueue::Command command);
    virtual void update(const PhantomTime& time);
    virtual void onCollision(Composite* other);
    void onTrigger();
    vector<Composite*> getSubscribers();

private:
    vector<Composite*> _subscribers;
    CommandQueue _commandQueue;
};


#endif // LightTrigger_H