#ifndef WORLD_H
#define	WORLD_H

#include <phantom.h>
#include <sharedlib/serialization/Serializable.h>

using namespace phantom;

using std::string;

class World {
public:
    World();
    virtual ~World();
    void generate(void);
    Data getSerializedData(void);

private:
    Layer _root;
};

#endif	/* WORLD_H */

