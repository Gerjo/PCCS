#ifndef BLOCKINGREADER_H
#define	BLOCKINGREADER_H

#include <yaxl.h>

#include "PacketReader.h"

class IPacketEventHandler {
public:
    virtual void onPacket(Packet* packet) = 0;
};

class ThreadedReader : public yaxl::concurrency::Thread, public IPacketEventHandler {
public:
    ThreadedReader(yaxl::socket::Socket* socket, IPacketEventHandler* handler = nullptr) :
            _socket(socket),
            _reader(nullptr),
            _handler(handler),
            _isAlive(true) {

    }

    virtual ~ThreadedReader(void) {
        _isAlive = false;

        delete _reader;
        _reader  = nullptr;
        _socket  = nullptr;
    }

    void forceQuit(void) {
        _isAlive = false;
        _socket->getInputStream().forceQuit();

        join();
    }

    void run(void) {
        _reader = new PacketReader(_socket->getInputStream());
        _reader->setBlocking(true);

        do {
            Packet* packet = _reader->readNext();
            if(!_isAlive) {
                cout << "Exiting thread, input reader was closed." << endl;
                break;
            }

            if(packet != nullptr) {
                // Aggregation:
                if(_handler != nullptr) {
                    _handler->onPacket(packet);

                // Inheritance:
                } else {
                    this->onPacket(packet);
                }

            } else {
                cout << "incomplete, fake packet or timeout." << endl;
            }

        } while(_isAlive);
    }

    virtual void onPacket(Packet* packet) {
        // override.
    }

private:
    IPacketEventHandler* _handler;
    PacketReader* _reader;
    yaxl::socket::Socket* _socket;
    bool _isAlive;
};

#endif	/* BLOCKINGREADER_H */

