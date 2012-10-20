#include "Player.h"

Player::Player(yaxl::socket::Socket* socket) {
    _socket = socket;

    identify();
}

void Player::identify(void) {
    Packet p(Packet::WHOAREYOU, "Who are you?");
    const char* bytes = p.getBytes();
    _socket->getOutputStream().write(p.getBytes(), p.length());

    delete[] bytes;
}

Player::~Player() {
    delete _socket;
}

