#include "Player.h"

Player::Player(yaxl::socket::Socket* socket) {
    _state        = NEWPLAYER;
    _socket       = socket;
    _packetReader = new PacketReader(_socket->getInputStream());
}

Player::~Player() {
    delete _socket;
}

void Player::run(void) {

    Packet* packet = _packetReader->readNext();

    if(packet != 0) {
        handlePacket(packet);
    }

    switch(_state) {
        case NEWPLAYER: {
            sendPacket(new Packet(PacketTypes::IDENT_WHOAREYOU, "Who are you?"));
            _state = IDENT_REQUESTED;
        } break;

        case IDENT_REQUESTED: {

        } break;
    }
}

void Player::handlePacket(Packet* packet) {
    cout << "Received: " << packet->getType() << endl;

    if(packet->getType() == IDENT_IAM) {
        sendPacket(new Packet(PacketTypes::IDENT_ACCEPTED, "Welcome."));

        _state = IDENT_ACCEPTED;
    } else if(packet->getType() == PING) {
        sendPacket(new Packet(PacketTypes::PONG, "PONG"));
    }



    delete packet;
}

void Player::sendPacket(Packet* packet) {
    cout << "Sending: " << packet->getType() << endl;

    const char* bytes = packet->getBytes();
    _socket->getOutputStream().write(packet->getBytes(), packet->length());

    delete[] bytes;
    delete packet;
}
