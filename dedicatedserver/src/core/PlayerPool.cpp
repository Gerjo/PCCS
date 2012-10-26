#include "PlayerPool.h"
#include "Player.h"
#include "GameHub.h"

PlayerPool::PlayerPool(GameHub* gamehub) : _playerUID(10) {
    _gamehub = gamehub;
}

PlayerPool::~PlayerPool() {
    for(Player* player : _players) {
        //player->join(); // NB: kill thread.
        delete player;
    }

    _players.clear();
}

PlayerModel PlayerPool::createPlayerModel(void) {
    PlayerModel model;

    // How unique, hah.
    model.id = _playerUID++;

    cout << "+ Registered new player with ID: #" << model.id << endl;

    return model;
}

void PlayerPool::addPlayer(Player* player) {
    yaxl::concurrency::ScopedLock lock(_playersMutex);
    _players.push_back(player);

    player->start();
}

void PlayerPool::broadcast(Packet* packet, const PlayerModel& exclude) {
    for(Player* player : _players) {
        if(player->model.id != exclude.id) {
            player->sendPacket(packet);
        }
    }

    packet->release();
}

// copy paste method from above, minus some checks.
void PlayerPool::broadcast(Packet* packet) {
    packet->retain();
    
    for(Player* player : _players) {
        player->sendPacket(packet);
    }

    packet->release();
}