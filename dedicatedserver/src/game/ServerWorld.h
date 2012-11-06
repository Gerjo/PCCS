#ifndef WORLD_H
#define	WORLD_H

#include <phantom.h>
#include <sharedlib/serialization/Serializable.h>
#include <sharedlib/models/PlayerModel.h>
#include <sharedlib/networking/networking.h>
#include <sharedlib/pathfinding/BSPTree.h>
#include <sharedlib/CommandQueue.h>
#include <sharedlib/serialization/Data.h>
#include "../Settings.h"
#include <yaxl.h>

using namespace phantom;

using std::string;
using yaxl::file::File;

class GameHub;

class ServerWorld : public yaxl::concurrency::Thread {
public:
    ServerWorld(GameHub* gamehub);
    virtual ~ServerWorld();
    void generate(void);
    Data getSerializedData(void);
    void spawnSoldiers(const PlayerModel& model);
    virtual void run(void);
    void selfPipe(Packet* packet);
    void addGameObject(GameObject* whom);

private:
    BSPTree* _root;
    GameHub* _gamehub;
    CommandQueue _commandQueue;

    void loadPrefab(void);
};

#endif	/* WORLD_H */

