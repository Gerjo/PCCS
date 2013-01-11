#ifndef BANDWIDTHTEST_H
#define	BANDWIDTHTEST_H

#include <phantom.h>
#include <sharedlib/networking/networking.h>

#include "Game.h"
#include "networking/Dedicated.h"

using namespace phantom;

class BandwidthTest : public Composite {
public:
    BandwidthTest() :
    _requestSent(false)
    {

    }

    void update(const PhantomTime& time) {
        return; // NB: disabled for now.
        if(!_requestSent) {
            static_cast<Game*>(getPhantomGame())->dedicated->sendPacket(
                new Packet(PacketType::REQUEST_LARGE_PACKET, "Requesting large packet.")
            );

            _requestTime = time.getTime();
            _requestSent = true;
        }
    }

    void onPacketReceived(Packet* packet) {
        if(packet->getType() == PacketType::REPLY_LARGE_PACKET) {
            float delay = static_cast<float>(phantom::Util::getTime() - _requestTime);
            size_t size = packet->getPayload().length();

            stringstream ss;

            ss << size << " bytes per " << delay << " seconds. ";

            static_cast<Game*>(getPhantomGame())->dedicated->sendBufferedMessage(
                new Message<string>("loader-text", ss.str())
            );
        }
    }
private:
    bool _requestSent;
    double _requestTime;
};

#endif	/* BANDWIDTHTEST_H */

