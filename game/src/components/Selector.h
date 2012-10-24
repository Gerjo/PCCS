#ifndef SELECTOR_H_GT
#define	SELECTOR_H_GT

#include <phantom.h>
#include <deque>
#include <sharedlib/gameobjects/HeavySoldier.h>

using namespace phantom;

using std::string;
using std::cout;
using std::endl;
using std::deque;

class Selector : public Composite {
public:
    Selector();
    virtual ~Selector();
    virtual void update(const float& elapsed);
    virtual MessageState handleMessage(AbstractMessage* message);

private:
    deque<HeavySoldier*> _soldiers;
};

#endif	/* SELECTOR_H_GT */
