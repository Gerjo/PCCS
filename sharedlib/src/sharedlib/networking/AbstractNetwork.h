#ifndef ABSTRACTNETWORK_H
#define	ABSTRACTNETWORK_H

#include <phantom.h>
#include <yaxl.h>
#include <sstream>
#include <iostream>
#include "networking.h"
#include "../serialization/Data.h"
#include "../SharedException.h"
#include "ThreadedWriter.h"

using namespace phantom;

using std::stringstream;
using std::endl;
using std::string;
using std::cout;

class AbstractNetwork : public IPacketEventHandler, public PacketEventMixin {
public:
    AbstractNetwork() :
        _socket(nullptr),
        _reader(nullptr),
        _writer(nullptr)
    {

    }

    virtual ~AbstractNetwork() {
        cout << "AbstractNetwork.cpp: _writer->forceQuit()" << endl;
        if(_writer != nullptr) {
            _writer->forceQuit();
        }

        cout << "AbstractNetwork.cpp: _reader->forceQuit()" << endl;
        if(_reader != nullptr) {
            _reader->forceQuit();
        }

        cout << "AbstractNetwork.cpp: Deleting _writer" << endl;
        delete _writer;       _writer       = nullptr;

        cout << "AbstractNetwork.cpp: Deleting _reader" << endl;
        delete _reader;       _reader       = nullptr;

        cout << "AbstractNetwork.cpp: Deleting _socket" << endl;
        delete _socket;       _socket       = nullptr;
    }

    void connect(string host, string port) {
        if(_socket != nullptr) {
            throw SharedException("This AbstractNetwork instance is already connected.");
        }

        try {
            _socket = new yaxl::socket::Socket(host, port);
            _socket->setTcpNoDelay(true);

            _reader  = new ThreadedReader(_socket, this);
            _reader->start();

            _writer = new ThreadedWriter(_socket);
            _writer->start();

            onConnectionSuccess();

        } catch(const yaxl::socket::SocketException& ex) {
            onConnectionFail(ex);
        }
    }

    // Default works, but feel free to implement your own.
    virtual void sendPacket(Packet* packet) {
        stringstream ss;
        ss << "> " << PacketTypeHelper::toString(packet->getType())
        << " (" << packet->getPayloadLength() << " bytes) ";

        cout << ss.str() << endl;

        _writer->write(packet);
    }

    // Default works, but feel free to implement your own.
    virtual void onPacket(Packet* packet) {
        stringstream ss;
        ss << "> " << PacketTypeHelper::toString(packet->getType())
        << " (" << packet->getPayloadLength() << " bytes, "
        << packet->estimatedLatency() << "ms) ";

        cout << ss.str() << endl;

        emitPacketEvent(packet);
    }

    // Virtuals provided by this class:
    virtual void onConnectionSuccess(void) = 0;
    virtual void onConnectionFail(const yaxl::socket::SocketException& ex) = 0;

private:
    yaxl::socket::Socket* _socket;
    ThreadedReader* _reader;
    ThreadedWriter* _writer;
};

#endif	/* ABSTRACTNETWORK_H */

