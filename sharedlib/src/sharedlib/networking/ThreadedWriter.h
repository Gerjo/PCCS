#ifndef THREADEDWRITER_H
#define	THREADEDWRITER_H

#include <yaxl.h>
#include <deque>

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

            stringstream ss;
            ss << "< " << PacketTypeHelper::toString(packet->getType()) << " (" << packet->getPayloadLength() << " bytes)";
            cout << ss.str() << endl;

            const char* bytes = packet->getBytes();

            _socket->getOutputStream().write(bytes, packet->length());

            // Leak, if exception is thrown.
            delete packet;
            delete[] bytes;

        } while(_isAlive);
    }

private:
    yaxl::socket::Socket* _socket;
    deque<Packet*> _buffer;
    yaxl::concurrency::Semaphore _semaphore;
    bool _isAlive;
};

#endif	/* THREADEDWRITER_H */



