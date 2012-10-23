#include "PlayerPool.h"
#include "Player.h"
#include "GameHub.h"

PlayerPool::PlayerPool(GameHub* gamehub) {
    _gamehub = gamehub;
}

PlayerPool::~PlayerPool() {
    for(Player* player : _players) {
        //player->join(); // NB: kill thread.
        delete player;
    }

    _players.clear();
}

void PlayerPool::addPlayer(Player* player) {
    yaxl::concurrency::ScopedLock lock(_playersMutex);
    _players.push_back(player);

    player->start();
}