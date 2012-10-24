#ifndef PLAYING_H
#define	PLAYING_H

#include <phantom.h>

using namespace phantom;

class World : public GameState {

public:
    World();
    virtual ~World();

    void init(void);
private:
};

#endif	/* PLAYING_H */

