#include "Ping.h"
#include "../Game.h"
#include "Network.h"
#include "src/gamestates/Loader.h"

Ping::Ping() :
        _isPingSent(false),
        _pingStartTime(0),
        _pingInterval(10),
        _lastPong(0),
        _currentPing(0)
{
    _game = static_cast<Game*>(getGame());
}

Ping::~Ping() {

}

void Ping::sendPing(void) {
    _game->network->sendPacket(new Packet(PacketType::PING, "PING"));

    _isPingSent    = true;
    _pingStartTime = phantom::Util::getTime();
}

void Ping::onPong(void) {
    double now   = phantom::Util::getTime();
    _currentPing = now - _pingStartTime;
    _isPingSent  = false;
    _lastPong    = now;

    stringstream ss;
    ss << "Roundtrip: " << _currentPing << " seconds.";

    _game->network->addText(ss.str());
}

void Ping::update(const float& elapsed) {
    if(!_isPingSent) {
        if(phantom::Util::getTime() - _lastPong > _pingInterval) {
            sendPing();
        }
    }
}

void Ping::onPacketReceived(Packet* packet) {
    if(packet->getType() == PacketType::PONG) {
        onPong();
    }
}

double Ping::getPing(void) {
    return _currentPing;
}