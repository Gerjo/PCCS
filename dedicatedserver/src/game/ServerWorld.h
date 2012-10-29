#ifndef WORLD_H
#define	WORLD_H

#include <phantom.h>
#include <sharedlib/serialization/Serializable.h>
#include <sharedlib/models/PlayerModel.h>
#include <sharedlib/networking/PacketType.h>
#include <sharedlib/pathfinding/BSPTree.h>
#include "../Settings.h"
#include <yaxl.h>

using namespace phantom;

using std::string;

class GameHub;

class ServerWorld : public yaxl::concurrency::Thread {
public:
    ServerWorld(GameHub* gamehub);
    virtual ~ServerWorld();
    void generate(void);
    Data getSerializedData(void);
    void spawnSoldier(const PlayerModel& model);
    virtual void run(void);

private:
    BSPTree* _root;
    GameHub* _gamehub;
};

#endif	/* WORLD_H */

