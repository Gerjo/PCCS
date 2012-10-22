#include "Ping.h"
#include "../Game.h"
#include "Network.h"
#include "src/gamestates/Loader.h"

Ping::Ping() : _isPingSent(false), _pingStartTime(0) {
    _game = static_cast<Game*>(getGame());
}

Ping::~Ping() {

}

void Ping::sendPing(void) {
    _game->network->sendPacket(new Packet(PacketTypes::PING, "PING"));

    _isPingSent    = true;
    _pingStartTime = phantom::Util::getTime();
}

void Ping::onPong(void) {

    stringstream ss;

    ss << "Roundtrip: " << (phantom::Util::getTime() - _pingStartTime) << " seconds.";

    _game->network->addText(ss.str());
    _isPingSent = false;
}

void Ping::update(const float& elapsed) {
    if(!_isPingSent) {
        sendPing();
    }
}

void Ping::onPacketReceived(Packet* packet) {
    if(packet->getType() == PacketTypes::PONG) {
        onPong();
    }
}