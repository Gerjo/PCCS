#include "PlayerPool.h"
#include "Player.h"
#include "GameHub.h"

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

PlayerModel *PlayerPool::exists(string nickname) {
    for(Player *p : _players) {
        // Since the current player is also in the _players pool, check if a nickname
        // is set. Yeah, this is a hack.
        if(p->model.nickname.empty()) {
            continue;
        }

        // TODO: Link to database.
        if(p->model.nickname.compare(nickname) == 0) {
            cout << "+ Reusing player with ID: #" << p->model.id << " and nickname: " << p->model.nickname << endl;
            return &p->model;
        }
    }
    return 0;
}

PlayerModel PlayerPool::createPlayerModel(string payload) {
    PlayerModel model;

    // How unique, hah.
    model.id = _playerUID++;
    model.nickname = payload;

    cout << "+ Registered new player with ID: #" << model.id << " and nickname: " << model.nickname << endl;

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
        if(player->model.id != exclude.id || Services::settings.dedicated_self_echo) {
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

void PlayerPool::broadcast(GameObject* recipient, Message<Data>* message) {
    Data data;
    data("UID_network") = recipient->UID_network;
    data("payload")     = message->getData();
    data("type")        = message->getType();

    delete message;

    Packet* packet = new Packet(PacketType::DIRECT_PIPE, data.toJson());

    broadcast(packet);
}