#ifndef ABSTRACTNETWORK_H
#define	ABSTRACTNETWORK_H

#include <phantom.h>
#include <yaxl.h>
#include <sstream>
#include <iostream>
#include <cstdio>
#include "ThreadedReader.h"
#include "ThreadedWriter.h"
#include "Packet.h"
#include "../serialization/Data.h"
#include "../SharedException.h"

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
        _writer(nullptr),
        _isConnected(false)
    {

    }

    bool isConnected() {
        return _isConnected;
    }

    virtual ~AbstractNetwork() {
        _isConnected = false;

        cout << "AbstractNetwork.cpp: _writer->forceQuit()" << endl;
        if(_writer != nullptr) {
            _writer->forceQuit();
        }

        cout << "AbstractNetwork.cpp: _reader->forceQuit()" << endl;
        if(_reader != nullptr) {
            _reader->forceQuit();
        }

        cout << "AbstractNetwork.cpp: Deleting _writer" << endl;
        delete _writer; _writer = nullptr;

        cout << "AbstractNetwork.cpp: Deleting _reader" << endl;
        delete _reader; _reader = nullptr;

        cout << "AbstractNetwork.cpp: Deleting _socket" << endl;
        delete _socket; _socket = nullptr;
    }

    void connect(string host, int port) {
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

            _isConnected = true;

            _reader->onDisconnect([this] {
                onDisconnect();
            });

            onConnectionSuccess();

        } catch(const yaxl::socket::SocketException& ex) {
            _isConnected = false;
            onConnectionFail(ex);
        }
    }

    // Default works, but feel free to implement your own.
    virtual void sendPacket(Packet* packet) {
        _writer->write(packet);
    }

    // Default works, but feel free to implement your own.
    virtual void onPacket(Packet* packet) {
        string aux;

        if(packet->getType() == PacketType::DIRECT_PIPE) {
            Data data = Data::fromJson(packet->getPayload());
            aux += " " + data("type").toString() + ",";
        }

        printf("> %s (%i byte(s),%s %llu ms)\n", PacketTypeHelper::toString(packet->getType()).c_str(), packet->getPayloadLength(), aux.c_str(), packet->estimatedLatency());

        PacketEventMixin::emitPacketEvent(packet);
    }

    // Virtuals provided by this class:
    virtual void onConnectionSuccess(void) = 0;
    virtual void onConnectionFail(const yaxl::socket::SocketException& ex) = 0;
    virtual void onDisconnect(void) = 0;

private:
    std::function<void(void)> _disconnectCallback;
    yaxl::socket::Socket* _socket;
    ThreadedReader* _reader;
    ThreadedWriter* _writer;
    bool _isConnected;
};

#endif	/* ABSTRACTNETWORK_H */

