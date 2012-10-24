#include "Player.h"

Player::Player(yaxl::socket::Socket* socket) {
    socket->setTcpNoDelay(true);
    _state        = NEWPLAYER;
    _socket       = socket;
    _packetReader = new PacketReader(_socket->getInputStream());
}

Player::~Player() {
    delete _socket;

    Packet* toSend;

    while((toSend = _sendBuffer.tryPop()) != 0) {
        delete toSend;
    }
}

void Player::readPackets(void) {
    Packet* packet = 0;

    try {
        packet = _packetReader->readNext();
    } catch(const yaxl::socket::SocketException& ex) {
        cout << "Error in reading: " << ex.what() << endl;
    }

    if(packet != 0) {
        handlePacket(packet);
    }
}

void Player::writePackets(void) {
    Packet* toSend;

    while((toSend = _sendBuffer.tryPop()) != 0) {

        const char* bytes = toSend->getBytes();

        try {
            _socket->getOutputStream().write(toSend->getBytes(), toSend->length());
        } catch(const yaxl::socket::SocketException& ex) {
            cout << "Error in writing: " << ex.what() << endl;
        }

        delete[] bytes;
        delete toSend;
    }
}

void Player::run(void) {
    do {

        readPackets();

        if(_state == NEWPLAYER) {
            sendPacket(new Packet(PacketTypes::IDENT_WHOAREYOU, "Who are you?"));
            _state = IDENT_REQUESTED;
        }

        writePackets();

        phantom::Util::sleep(200);
    } while(true);
}

void Player::handlePacket(Packet* packet) {
    //cout << "Handling packet: " << packet->getType() << " (" << packet->getPayload() << ")" << endl;

    if(packet->getType() == IDENT_IAM) {
        sendPacket(new Packet(PacketTypes::IDENT_ACCEPTED, "Welcome."));

        _state = IDENT_ACCEPTED;
    } else if(packet->getType() == PING) {
        sendPacket(new Packet(PacketTypes::PONG, "PONG"));

    } else if(packet->getType() == REQUEST_LARGE_PACKET) {
        string str;

        for(int i = 0; i < 10000000; ++i) {
            str.append("l");
        }

        sendPacket(new Packet(PacketTypes::REPLY_LARGE_PACKET, str));
    }

    delete packet;
}

void Player::sendPacket(Packet* packet) {
    _sendBuffer.push(packet);
}
