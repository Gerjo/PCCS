#ifndef BANDWIDTHTEST_H
#define	BANDWIDTHTEST_H

#include <phantom.h>
#include <Packet.h>
#include <PacketTypes.h>

#include "Game.h"
#include "networking/Network.h"

using namespace phantom;

class BandwidthTest : public Composite {
public:
    BandwidthTest() :
    _requestSent(false)
    {

    }

    void update(const float& elapsed) {
        if(!_requestSent) {
            static_cast<Game*>(getGame())->network->sendPacket(
                new Packet(PacketTypes::REQUEST_LARGE_PACKET, "Requesting large packet.")
            );

            _requestTime = phantom::Util::getTime();
            _requestSent = true;
        }
    }

    void onPacketReceived(Packet* packet) {
        if(packet->getType() == PacketTypes::REPLY_LARGE_PACKET) {
            float delay = phantom::Util::getTime() - _requestTime;
            int size = packet->getPayload().length();

            stringstream ss;



            ss << size << " bytes per " << delay << " seconds. ";


            static_cast<Game*>(getGame())->network->sendBufferedMessage(
                new Message<string>("loader-text", ss.str())
            );
        }
    }
private:
    bool _requestSent;
    double _requestTime;
};

#endif	/* BANDWIDTHTEST_H */
