#ifndef THREADEDWRITER_H
#define	THREADEDWRITER_H

#include <yaxl.h>
#include <deque>
#include "Packet.h"
#include "PacketType.h"
#include <cstdio>

using std::deque;

class ThreadedWriter : public yaxl::concurrency::Thread {
public:
    ThreadedWriter(yaxl::socket::Socket* socket) : _socket(socket), _isAlive(true), _semaphore(0) {

    }

    ~ThreadedWriter(void) {

    }

    void forceQuit(void) {
        _isAlive = false;
        _semaphore.signal();
        join();
    }

    void write(Packet* packet) {
        _buffer.push_front(packet);
        _semaphore.signal();
    }

    void run(void) {
        do {
            _semaphore.wait();
            if(!_isAlive) {
                break;
            }

            Packet* packet = _buffer.back();
            _buffer.pop_back();

            printf("< %s (%i byte(s))\n", PacketTypeHelper::toString(packet->getType()).c_str(), packet->getPayloadLength());

            const char* bytes = packet->getBytes();

            bool hasError = false;

            try {
                _socket->getOutputStream().write(bytes, static_cast<const int>(packet->length()));

            // Catch any exceptions. If we don't catch everything here, we risk
            // a memory leak.
            } catch(...) {
                hasError = true;
            }

            // Leak, if exception is thrown.
            delete packet;
            delete[] bytes;

            // All data has been "deleted", re throw the exception.
            if(hasError) {
                cout << "ThreadedWriter::run(): exception is about to be thrown." << endl;
                throw;
            }

        } while(_isAlive);
    }

private:
    yaxl::socket::Socket* _socket;
    deque<Packet*> _buffer;
    yaxl::concurrency::Semaphore _semaphore;
    bool _isAlive;
};

#endif	/* THREADEDWRITER_H */



