#include "Player.h"

Player::Player(yaxl::socket::Socket* socket) {
    _socket = socket;
}

Player::~Player() {
    delete _socket;
}

