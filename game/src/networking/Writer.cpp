#include "Writer.h"

Writer::Writer(Network& network) : _network(network), isAlive(true), _semaphore(0) {

}

Writer::~Writer() {

    forceQuit();


    while(!_buffer.empty()) {
        Packet* packet = _buffer.front();
        delete packet;
        packet = nullptr;

        _buffer.pop_front();
    }
}

void Writer::forceQuit(void) {
    // Set the dead flag.
    isAlive = false;

    // Wakeup the thread, when woken up, it will trip over the "isAlive" flag
    // and halt itself.
    _semaphore.signal();
}

void Writer::sendPacket(Packet* packet) {
    _buffer.push_front(packet);
    _semaphore.signal();
}

void Writer::run(void) {
    do {
        _semaphore.wait();

        // We might've been woken up due to a "forceQuit" call.
        if(!isAlive) {
            break;
        }

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
