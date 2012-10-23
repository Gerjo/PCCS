#ifndef WORLD_H
#define	WORLD_H

#include <phantom.h>

using namespace phantom;

class World {
public:
    World();
    virtual ~World();
    void generate(void);

private:
    Layer _root;
};

#endif	/* WORLD_H */

