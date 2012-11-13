#ifndef WORLD_H
#define	WORLD_H

#include <phantom.h>
#include <sharedlib/serialization/Serializable.h>
#include <sharedlib/models/PlayerModel.h>
#include <sharedlib/networking/networking.h>
#include <sharedlib/pathfinding/BSPTree.h>
#include <sharedlib/CommandQueue.h>
#include <sharedlib/serialization/Data.h>
#include <sharedlib/missions/Mission.h>
#include "../Settings.h"
#include <yaxl.h>

using namespace phantom;

using std::string;
using yaxl::file::File;

class GameHub;

class ServerWorld : public GameState {
public:
    ServerWorld(GameHub* gamehub);
    virtual ~ServerWorld();
    void generate(void);
    Data getSerializedData(void);
    void spawnSoldiers(const PlayerModel& model);
    void selfPipe(Packet* packet);
    void addGameObject(GameObject* whom);
    virtual void update(const Time& time);

private:
    BSPTree* _root;
    GameHub* _gamehub;
    CommandQueue _commandQueue;
    Mission* mission;
    void loadPrefab(void);
};

#endif	/* WORLD_H */

