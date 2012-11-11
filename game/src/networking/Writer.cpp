#include "Writer.h"

Writer::Writer(Network& network) : _network(network), isAlive(true), _semaphore(0) {

}

Writer::~Writer() {
    Packet* packet;
    while((packet = _buffer.tryPop()) != 0) {
        delete packet;
    }
}

void Writer::sendPacket(Packet* packet) {
    _buffer.push(packet);
    _semaphore.signal();
}

void Writer::run(void) {
    do {
        _semaphore.wait();

        Packet* packet;
        if((packet = _buffer.tryPop()) != 0) {
            stringstream ss;
            ss << "< " << PacketTypeHelper::toString(packet->getType()) << " (" << packet->getPayloadLength() << " bytes)";
            _network.addText(ss.str());
            cout << ss.str() << endl;

            const char* bytes = packet->getBytes();
            _network.getOutputStream().write(bytes, packet->length());

            delete packet;
            delete[] bytes;
        }

        //sleep(123);
    } while(isAlive);
}

// 11:00