/*
 * File:   Client.h
 * Author: gerjo
 *
 * Created on November 15, 2012, 1:53 PM
 */

#ifndef CLIENT_H
#define	CLIENT_H

#include <yaxl.h>
#include <sharedlib/networking/networking.h>
#include <sstream>

using std::stringstream;
using std::count;
using std::endl;

class Master;

class Client : public ThreadedReader {
public:
    Client(yaxl::socket::Socket* socket, Master* master);
    virtual ~Client();
    virtual void onPacket(Packet* packet);
    void write(Packet* packet);
    yaxl::socket::Socket* getSocket();

private:
    yaxl::socket::Socket* _socket;
    Master* _master;
};

#endif	/* CLIENT_H */

