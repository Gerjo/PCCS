#ifndef WORLD_H
#define	WORLD_H

#include <phantom.h>
#include <sharedlib/models/PlayerModel.h>
#include <sharedlib/networking/networking.h>
#include <sharedlib/pathfinding/BSPTree.h>
#include <sharedlib/CommandQueue.h>
#include <sharedlib/serialization/Data.h>
#include <sharedlib/missions/Mission.h>
#include <yaxl.h>
#include <set>
#include <Procedural.h>

using namespace phantom;

using std::string;
using yaxl::file::File;

class GameHub;
class Player;
class Procedural;

class ServerWorld : public GameState {
public:
    vector<Center*> spawnLocations;


    ServerWorld(GameHub* gamehub);
    virtual ~ServerWorld();
    void generate(void);
    Data getSerializedData(void);
    void getSerializedDataAsync(Player* player);
    Procedural* getProceduralGeneratedContent();
    void selfPipe(Packet* packet);
    void addGameObject(GameObject* whom);
    virtual void update(const PhantomTime& time);

private:
    BSPTree* _root;
    GameHub* _gamehub;
    CommandQueue _commandQueue;
    Mission* mission;
    Procedural* _proc;
    const static unsigned int TREE_AMOUNT;
    const static unsigned int ENEMY_AMOUNT;

    void loadPrefab(void);
    void loadProceduralLevel(void);
    void createObjectives(Procedural& proc);
    void createStaticObjects(Procedural& proc);
    void createEnemies(Procedural& proc);

    std::set<Center*> centersWithTree;
};

#endif	/* WORLD_H */

