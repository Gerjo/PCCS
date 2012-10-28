#include "PlayerPool.h"
#include "Player.h"
#include "GameHub.h"

PlayerPool::PlayerPool(GameHub* gamehub) : _playerUID(10) {
    _gamehub = gamehub;
}

PlayerPool::~PlayerPool() {
    //for(Player* player : _players) {
        //player->join(); // NB: kill thread. Disconnect? There is no
        // real client way to delete this. (not yet)
        //delete player;
    //}

    //_players.clear();
}


void PlayerPool::run(void) {
    do {
        _playersMutex.lock();
        cout << "Start deletion run:" << endl;

        for(auto it = _players.begin(); it != _players.end(); ++it) {
            Player* player = *it;

            if(player->shouldDelete()) {
                it = _players.erase(it);

                // Normally this is pretty unsafe, but we're deleting the thread
                // right away, so it's OK.
                player->detach();

                delete player;

                if(it == _players.end()) {
                    break;
                }
            }
        }
        _playersMutex.unlock();

        phantom::Util::sleep(2000);
    } while(true);
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