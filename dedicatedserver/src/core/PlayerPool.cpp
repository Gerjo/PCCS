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