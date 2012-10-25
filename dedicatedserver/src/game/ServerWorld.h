#ifndef WORLD_H
#define	WORLD_H

#include <phantom.h>
#include <sharedlib/serialization/Serializable.h>
#include <sharedlib/models/PlayerModel.h>
#include <sharedlib/networking/PacketType.h>

using namespace phantom;

using std::string;

class GameHub;

class ServerWorld {
public:
    ServerWorld(GameHub* gamehub);
    virtual ~ServerWorld();
    void generate(void);
    Data getSerializedData(void);
    void spawnSoldier(const PlayerModel& model);

private:
    Layer _root;
    GameHub* _gamehub;
};

#endif	/* WORLD_H */

