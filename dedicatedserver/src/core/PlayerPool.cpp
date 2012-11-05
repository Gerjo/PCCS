#include "PlayerPool.h"
#include "Player.h"
#include "GameHub.h"
#include <sharedlib/SharedSettings.h>
PlayerPool::PlayerPool(GameHub* gamehub) : _playerUID(10) {
    _gamehub = gamehub;
}

PlayerPool::~PlayerPool() {
    // TODO: delete and disconnect players.
}

void PlayerPool::run(void) {
    do {
        _playersMutex.lock();

        for(auto it = _players.begin(); it != _players.end(); ++it) {
            Player* player = *it;

            if(player->shouldDelete()) {
                cout << "+ Player garbage collector, deleting: " << player->toString() << endl;

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

        // Odd delay, we're probably adding more sleeps, so this way they won't
        // all wake at the same time.
        sleep(7336);
    } while(true);
}
bool PlayerPool::playerExist(void){
    unsigned int id;
    id = SharedSettings::UNIQUE_ID();

    deque<Player*>::iterator it;
    for(it = _players.begin(); it < _players.end(); ++it){
        if((*it)->model.id == id){
            return true;
        }
    }
    return false;
}
PlayerModel PlayerPool::createPlayerModel(void) {
    unsigned int id;
    id = SharedSettings::UNIQUE_ID();

    PlayerModel model;

    // How unique, hah.
    model.id = id;

    cout << "+ Registered new player with ID: #" << model.id << endl;

    return model;
}

void PlayerPool::addPlayer(Player* player) {
    yaxl::concurrency::ScopedLock lock(_playersMutex);
    _players.push_back(player);

    player->start();
}

void PlayerPool::broadcast(Packet* packet, const PlayerModel& exclude) {
    packet->retain();

    for(Player* player : _players) {
        if(player->model.id != exclude.id || Settings::BROADCAST_SELF_ECHO) {
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