#include "PlayerPool.h"
#include "Player.h"
#include "GameHub.h"

PlayerPool::PlayerPool(GameHub* gamehub) {
    _gamehub = gamehub;
}

PlayerPool::~PlayerPool() {
    for(Player* player : _players) {
        delete player;
    }

    _players.clear();
}

void PlayerPool::run(void) {
    do {
        _playersMutex.lock();

        for(Player* player : _players) {
            player->run();
        }

        _playersMutex.unlock();

        phantom::Util::sleep(200);
    } while(1);
}

void PlayerPool::addPlayer(Player* player) {
    yaxl::concurrency::ScopedLock lock(_playersMutex);
    _players.push_back(player);
}