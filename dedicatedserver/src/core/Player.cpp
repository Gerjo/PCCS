#include "Player.h"
#include "GameHub.h"

Player::Player(GameHub* gamehub, yaxl::socket::Socket* socket) : _gamehub(gamehub) {
    socket->setTcpNoDelay(true);
    _state        = NEWPLAYER;
    _socket       = socket;
    _packetReader = new PacketReader(_socket->getInputStream());


    registerEvent(IDENT_IAM, [this] (Packet* packet) -> Packet* {
        _state = IDENT_ACCEPTED;
        return new Packet(PacketType::IDENT_ACCEPTED, "Welcome.");
    });

    registerEvent(PING, [this] (Packet* packet) -> Packet* {
        return new Packet(PacketType::PONG, "PONG");
    });

    registerEvent(REQUEST_LARGE_PACKET, [this] (Packet* packet) -> Packet* {
        string str;
        str.insert(0, 1000000, 'X');

        return new Packet(PacketType::REPLY_LARGE_PACKET, str);
    });

    registerEvent(REQUEST_GAMEWORLD, [this] (Packet* packet) -> Packet* {
        string world = _gamehub->world.getSerializedData().toJson();

        return new Packet(PacketType::REPLY_GAMEWORLD, world);
    });
}

Player::~Player() {
    delete _socket;

    // There may be stuff left in the send queue:
    Packet* toSend;
    while((toSend = _sendBuffer.tryPop()) != 0) {
        delete toSend;
    }
}

void Player::registerEvent(PacketType type, PacketEvent event) {
    _packetEvents.insert(std::pair<PacketType, PacketEvent>(
        type, event
    ));
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
        cout << "< " << PacketTypeHelper::toString(toSend->getType()) << " (" << toSend->getPayloadLength() << " bytes)" << endl;

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


void Player::takeInitiative() {

    if(_state == NEWPLAYER) {
        sendPacket(new Packet(PacketType::IDENT_WHOAREYOU, "Who are you?"));
        _state = IDENT_REQUESTED;
    }

}

void Player::run(void) {
    do {
        // Reads all packets (if any) then calls "handlePacket" for each packet.
        readPackets();

        // So events are only triggered by requests from the client. In this method
        // we permit the server to take initiative, and contact the client without
        // the client placing a request first.
        takeInitiative();

        // Send any buffered packets to the client. This *should* go
        // async eventually.
        writePackets();

        // This is here to cut my CPU some slack. Eventually this should be
        // a true event based system, and thus no need for busy waiting stuff.
        phantom::Util::sleep(200);
    } while(true);
}

void Player::handlePacket(Packet* packet) {
    const PacketType type = (PacketType) packet->getType();

    cout << "> " << PacketTypeHelper::toString(type) << " (" << packet->getPayloadLength() << " bytes)" << endl;

    if(_packetEvents.find(type) != _packetEvents.end()) {
        PacketEvent& handler = _packetEvents[type];

        Packet* reply = handler(packet);

        if(reply != 0) {
            sendPacket(reply);
        }
    }

    delete packet;
}

void Player::sendPacket(Packet* packet) {
    _sendBuffer.push(packet);
}
