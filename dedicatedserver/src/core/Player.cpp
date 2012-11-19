#include "Player.h"
#include "GameHub.h"
#include "PlayerPool.h"
#include <sharedlib/SharedSettings.h>
#include "../NetworkFactory.h"

Player::Player(GameHub* gamehub, yaxl::socket::Socket* socket) : _gamehub(gamehub), authState(ROGUE),
    _authDeadline(Services::settings().dedicated_auth_gracetime),
    _pingDeadline(Services::settings().dedicated_ping_gracetime),
    _isThreadRunning(false) {

        socket->setTcpNoDelay(true);
        _socket       = socket;
        _packetReader = new PacketReader(_socket->getInputStream());


        registerPacketEvent(PING, [this] (Packet* packet) -> Packet* {
            _pingDeadline.restart();
            return new Packet(PacketType::PONG);
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

        registerPacketEvent(REQUEST_INTRODUCE, [this] (Packet* packet) -> Packet* {
            Data data = Data::fromJson(packet->getPayload());


            GameObject* gameobject = NetworkFactory::create(data("type"));

            // Overrides UID_network :(
            gameobject->fromData(data);
            _gamehub->world->addGameObject(gameobject);

            Data spawnData;
            gameobject->toData(spawnData("dynamic")(gameobject->UID_network));

            Packet* spawnPacket = new Packet(PacketType::PUSH_GAMEOBJECTS, spawnData.toJson());
            _gamehub->pool->broadcast(spawnPacket, model);

            // We send a reply with the network UID of this component. The client
            // can then assign this UID_network himself.
            Data reply;
            reply("UID_network") = gameobject->UID_network;
            reply("UID_local")   = data("UID_local");
            return new Packet(PacketType::ACCEPTED_INTRODUCE, reply.toJson());
        });

        registerPacketEvent(DIRECT_PIPE, [this] (Packet* packet) -> Packet* {
            // TODO: sanity check. We we want to proxy everything?

            // Proxy the message to all other players. Of course excluding
            // the originator. This is some nifty stuff right here. -- Gerjo
            _gamehub->pool->broadcast(packet, model);
            _gamehub->world->selfPipe(packet);

            // TODO: broadcast in the server tree, too. For this to work, some
            // pathfinding features should probably be made agnostic to server/
            // client details.

            // Could reply an "ack" here, incase we go UDP.
            return 0;
        });

        registerPacketEvent(SERVER_PIPE, [this] (Packet* packet) -> Packet* {
            _gamehub->world->selfPipe(packet);
            //cout << "!! I am delighted to handle your message, kind Sir. Payload:" << packet->getPayload() << endl;
            return 0;
        });

        cout << "+ " << toString() << " Accepted socket. Starting auth procedure. " << endl;
}

Player::~Player() {
    delete _socket;

    // There may be stuff left in the send queue:
    //Packet* toSend;
    //while((toSend = _sendBuffer.tryPop()) != 0) {
    //    delete toSend;
    //}
}

void Player::readPackets(void) {
    Packet* packet = 0;

    do {
        try {
            packet = _packetReader->readNext();

            if(packet != 0) {
                handlePacket(packet);
            }

        } catch(const yaxl::socket::SocketException& ex) {
            cout << "+ " << toString() <<  " Error in reading: " << ex.what() << " closing connection. " << endl;
            disconnect();
        }

    } while(packet != 0);
}

void Player::writePackets(void) {
    if(!_sendBuffer.empty()) {
        Packet* packet = _sendBuffer.back();
        _sendBuffer.pop_back();

        printf("< %s %s (%i byte(s))\n", toString().c_str(), PacketTypeHelper::toString(packet->getType()).c_str(), packet->getPayloadLength());

        const char* bytes = packet->getBytes();

        try {
            _socket->getOutputStream().write(packet->getBytes(), packet->length());
        } catch(const yaxl::socket::SocketException& ex) {
            cout << "+ " << toString() << " Player::writePackets -> " << ex.what() << " closing connection. " << endl;
            disconnect();
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
            sendPacket(new Packet(PacketType::YOU_TIMED_OUT, "Your ping interval is too low."));
            disconnect();
        }
    }
}

void Player::run(void) {
    _isThreadRunning = true;

    do {
        // Handle all timed events. Mostly ping related stuff. This must be called
        // first, since it *may* send packets, and thus needs a "writePackets" call.
        handleDeadlines();

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
        sleep(60);
    } while(authState != DISCONNECTED);

    clearPacketEvents();
    _socket->close();


    _isThreadRunning = false;
}

void Player::handlePacket(Packet* packet) {

    printf("> %s %s (%i byte(s), %llu ms)\n", toString().c_str(), PacketTypeHelper::toString(packet->getType()).c_str(), packet->getPayloadLength(), packet->estimatedLatency());


    // Use packet events only when authenticated, this should prevent us from
    // sending data to rogue clients such as port scanners we just happen
    // to guess the right byte sequence.
    if(authState == AUTHENTICATED) {
         _pingDeadline.restart(); // Count any packet as a ping too.
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

        // Give one free PING:
        _pingDeadline.restart();

        PlayerModel *retrievedModel = _gamehub->pool->exists(packet->getPayload());

        if(retrievedModel == 0) {
            model = _gamehub->pool->createPlayerModel(packet->getPayload());
            // TODO: first sync the world, then spawn?

            loadSoldiers();

            Data data;
            for(LightSoldier* soldier : _soldiers) {
                _gamehub->world->addGameObject(soldier);

                // Serialize this instance so we can push it to all players:
                soldier->toData(data("dynamic")(soldier->UID_network));
            }

            _gamehub->pool->broadcast(new Packet(PacketType::PUSH_GAMEOBJECTS, data.toJson()), model);
        } else {
            model = *retrievedModel;
        }

        sendPacket(new Packet(PacketType::IDENT_ACCEPTED, model.toData().toJson()));
    }
}

void Player::sendPacket(Packet* packet) {
    packet->retain();
    _sendBuffer.push_front(packet);
}

void Player::disconnect() {
    authState = DISCONNECTED;

    Data data;


    for(LightSoldier* soldier : _soldiers) {
        // Messages are automatically deleted, so create one per iteration.
        Services::broadcast(soldier, new Message<Data>("disconnect", data));

        // Delete soldiers server side, too. The destroy method will handle
        // any concurrency issues automatically.
        soldier->destroy();
    }

    _soldiers.clear();
}

bool Player::shouldDelete() {
    // Only destroy if we're really dead:
    return authState == DISCONNECTED && !_isThreadRunning;
}

string Player::toString() {
    stringstream ss;
    ss << "[" << model.id << " at " << _socket->getFd() << "]";
    return ss.str();
}

void Player::loadSoldiers(void) {
    for(int i = 0; i < 5; ++i) {
        LightSoldier* soldier = static_cast<LightSoldier*>(NetworkFactory::create("soldier"));

        // Bind this soldier to an owner:
        soldier->playerId     = model.id;

        // TODO: Realistic spawn location:
        soldier->setPosition(Vector3(20.0f + i * (soldier->getBoundingBox().size.x + 10), (40.0f * model.id) + (i * 5.0f), 0.0f));

        _soldiers.push_back(soldier);
    }
}
