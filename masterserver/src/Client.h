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

using std::count;
using std::endl;

class Master;

class Client : public BlockingReader {
public:
    Client(yaxl::socket::Socket* socket, Master* master);
    virtual ~Client();
    virtual void onPacket(Packet* packet);
    
private:
    yaxl::socket::Socket* _socket;
    Master* _master;
};

#endif	/* CLIENT_H */
