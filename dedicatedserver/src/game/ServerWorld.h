#ifndef WORLD_H
#define	WORLD_H

#include <phantom.h>
#include <sharedlib/serialization/Serializable.h>
#include <sharedlib/models/PlayerModel.h>

using namespace phantom;

using std::string;

class ServerWorld {
public:
    ServerWorld();
    virtual ~ServerWorld();
    void generate(void);
    Data getSerializedData(void);
    void spawnSoldier(const PlayerModel& model);

private:
    Layer _root;
};

#endif	/* WORLD_H */

