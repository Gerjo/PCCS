#include "Writer.h"

Writer::Writer(Network& network) : _network(network), isAlive(true), _semaphore(0) {

}

Writer::~Writer() {

    while(!_buffer.empty()) {
        Packet* packet = _buffer.front();
        delete packet;
        packet = nullptr;

        _buffer.pop_front();
    }
}

void Writer::sendPacket(Packet* packet) {
    _buffer.push_front(packet);
    _semaphore.signal();
}

void Writer::run(void) {
    do {
        _semaphore.wait(); // TODO: destructor?

        Packet* packet = _buffer.back();
        _buffer.pop_back();

        stringstream ss;
        ss << "< " << PacketTypeHelper::toString(packet->getType()) << " (" << packet->getPayloadLength() << " bytes)";
        _network.addText(ss.str());
        cout << ss.str() << endl;

        const char* bytes = packet->getBytes();
        _network.getOutputStream().write(bytes, packet->length());

        delete packet;
        delete[] bytes;

    } while(isAlive);
}
