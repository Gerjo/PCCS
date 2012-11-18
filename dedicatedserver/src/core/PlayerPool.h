#ifndef PLAYERPOOL_H
#define	PLAYERPOOL_H

#include <deque>
#include <iostream>
#include <string>
#include <yaxl.h>
#include <vector>
#include <sharedlib/models/PlayerModel.h>
#include <sharedlib/networking/Packet.h>
#include <sharedlib/services/Services.h>
#include <sharedlib/gameobjects/LightSoldier.h>

class Player;
class GameHub;

using std::vector;

class PlayerPool : public yaxl::concurrency::Thread, public IBroadcast {
public:
    PlayerPool(GameHub* gamehub);
    ~PlayerPool();
    void addPlayer(Player* player);

    PlayerModel *exists(string nickname);
    PlayerModel createPlayerModel(string payload);


    void broadcast(Packet* packet, const PlayerModel& exclude);
    void broadcast(Packet* packet);

    // Service implementation:
    void broadcast(GameObject* recipient, Message<Data>* message);

    void run(void);

private:
    deque<Player*> _players;
    GameHub* _gamehub;
    yaxl::concurrency::Mutex _playersMutex;

    int _playerUID;
};

#endif	/* PLAYERPOOL_H */

