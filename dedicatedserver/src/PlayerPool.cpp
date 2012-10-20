#include "PlayerPool.h"
#include "Player.h"
#include "GameHub.h"

PlayerPool::PlayerPool(GameHub* gamehub) {
    _gamehub = gamehub;
}

PlayerPool::~PlayerPool() {
    for(auto it = _players.begin(); it != _players.end(); ++it) {
        delete *it;
    }

    _players.clear();
}

void PlayerPool::addPlayer(Player* player) {
    _players.push_back(player);
}