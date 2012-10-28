#include "Player.h"
#include "GameHub.h"
#include "PlayerPool.h"
#include "src/Settings.h"

Player::Player(GameHub* gamehub, yaxl::socket::Socket* socket) : _gamehub(gamehub), authState(ROGUE),
    _authDeadline(Settings::AUTH_GRACE_TIME), _pingDeadline(Settings::PING_GRACE_TIME), _isThreadRunning(false) {

    socket->setTcpNoDelay(true);
    _socket       = socket;
    _packetReader = new PacketReader(_socket->getInputStream());


    registerPacketEvent(PING, [this] (Packet* packet) -> Packet* {
        _pingDeadline.restart();
        return new Packet(PacketType::PONG, "PONG");
    });

    registerPacketEvent(REQUEST_LARGE_PACKET, [this] (Packet* packet) -> Packet* {
        string str;
        str.insert(0, 1000000, 'X');

        return new Packet(PacketType::REPLY_LARGE_PACKET, str);
    });

    registerPacketEvent(REQUEST_GAMEWORLD, [this] (Packet* packet) -> Packet* {
        string world = _gamehub->world->getSerializedData().toJson();

        return new Packet(PacketType::REPLY_GAMEWORLD, world);
    });

    registerPacketEvent(DIRECT_PIPE, [this] (Packet* packet) -> Packet* {
        // TODO: sanity check. We we want to proxy everything?

        // Proxy the message to all other players. Of course excluding
        // the originator. This is some nifty stuff right here. -- Gerjo
        _gamehub->pool->broadcast(packet, model);

        // TODO: broadcast in the server tree, too. For this to work, some
        // pathfinding features should probably be made agnostic to server/
        // client details.

        // Could reply an "ack" here, incase we go UDP.
        return 0;
    });

    cout << "+ " << toString() << " Accepted socket. Starting auth procedure. " << endl;
}

Player::~Player() {
    delete _socket;

    // There may be stuff left in the send queue:
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
        cout << "+ " << toString() <<  " Error in reading: " << ex.what() << endl;
    }

    if(packet != 0) {
        handlePacket(packet);
    }
}

void Player::writePackets(void) {
    Packet* packet;

    while((packet = _sendBuffer.tryPop()) != 0) {

        cout << "< " << toString() << " "
             << PacketTypeHelper::toString(packet->getType())
             << " (" << packet->getPayloadLength() << " bytes)" << endl;

        const char* bytes = packet->getBytes();

        try {
            _socket->getOutputStream().write(packet->getBytes(), packet->length());
        } catch(const yaxl::socket::SocketException& ex) {
            cout << "+ " << toString() << " Player::writePackets -> Error in writing: " << ex.what() << endl;
        }

        delete[] bytes;
        packet->release();
    }
}

void Player::takeInitiative() {
    // Yeah, we take little initiative.
}

void Player::handleDeadlines() {
    if(authState != AUTHENTICATED) {
        if(_authDeadline.hasExpired()) {
            cout << "+ " << toString() << " Authentication took too long. Marking client for disconnect." << endl;
            disconnect();
        }

    } else {
        if(_pingDeadline.hasExpired()) {
            cout << "+ " << toString() << " A ping timeout was reached. Marking client for disconnect." << endl;
            disconnect();
        }
    }
}

void Player::run(void) {
    _isThreadRunning = true;

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

        // Handle all timed events. Mostly ping related stuff.
        handleDeadlines();

        // This is here to cut my CPU some slack. Eventually this should be
        // a true event based system, and thus no need for busy waiting stuff.
        phantom::Util::sleep(200);
    } while(authState != DISCONNECTED);

    clearPacketEvents();
    _socket->close();


    _isThreadRunning = false;
}

void Player::handlePacket(Packet* packet) {
    cout << "> " << toString() << " " << PacketTypeHelper::toString(packet->getType()) << " (" << packet->getPayloadLength() << " bytes)" << endl;

    // Use packet events only when authenticated, this should prevent us from
    // sending data to rogue clients such as port scanners we just happen
    // to guess the right byte sequence.
    if(authState == AUTHENTICATED) {
        // _pingDeadline.reset(); // Not just yet.
        emitPacketEvent(packet);
        return;
    }

    // We're dealing with an unknown, possible rogue connection. Only permit
    // minimal packet types:
    if(packet->getType() == IDENT_LETSCONNECT) {
        sendPacket(new Packet(PacketType::IDENT_WHOAREYOU, "Sounds fun! But who are you?"));

    } else if(packet->getType() == IDENT_IAM) {
        // TODO: some sort of lookup or auth system. For now we'll just create
        // everything brand new each time someone connects.
        authState = AUTHENTICATED;
        model     = _gamehub->pool->createPlayerModel();

        // Give one free PING:
        _pingDeadline.restart();

        // TODO: first sync the world, then spawn?
        _gamehub->world->spawnSoldier(model);

        sendPacket(new Packet(PacketType::IDENT_ACCEPTED, model.toData().toJson()));
    }
}

void Player::sendPacket(Packet* packet) {
    packet->retain();
    _sendBuffer.push(packet);
}

void Player::disconnect() {
    authState = DISCONNECTED;
}

bool Player::shouldDelete() {
    // Only destroy if we're really dead:
    return authState == DISCONNECTED && !_isThreadRunning;
}

string Player::toString() {
    stringstream ss;
    ss << "[" << model.id << " at " << _socket->getFd() << "] ";
    return ss.str();
}