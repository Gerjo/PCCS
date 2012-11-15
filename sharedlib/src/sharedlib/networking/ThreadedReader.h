#ifndef BLOCKINGREADER_H
#define	BLOCKINGREADER_H

#include <yaxl.h>
#include <functional>
#include "../SharedException.h"
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
            _disconnectCallback = nullptr;
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

        if(joinable()) {
            join();
        }
    }

    void run(void) {
        _reader = new PacketReader(_socket->getInputStream());
        _reader->setBlocking(true);

        do {
            Packet* packet = nullptr;

            try {
                packet = _reader->readNext();

            } catch(const yaxl::socket::DisconnectedException& e) {
                _isAlive = false;

                if(_disconnectCallback != nullptr) {
                    _disconnectCallback();

                } else {
                    throw SharedException("A socket disconnected, but no onDisconnect handler was set.");
                }

                break;
            }

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

    void onDisconnect(std::function<void(void)> callback) {
        _disconnectCallback = callback;
    }

    virtual void onPacket(Packet* packet) {
        // override.
    }

private:
    IPacketEventHandler* _handler;
    PacketReader* _reader;
    yaxl::socket::Socket* _socket;
    bool _isAlive;
    std::function<void(void)> _disconnectCallback;
};

#endif	/* BLOCKINGREADER_H */

