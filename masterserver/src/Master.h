/*
 * File:   Master.cpp
 * Author: gerjo
 *
 * Created on November 15, 2012, 1:47 PM
 */

#ifndef MASTER_H
#define	MASTER_H

#include <deque>
#include <iostream>
#include <functional>
#include <sharedlib/serialization/Data.h>
#include "storage/DataInterface.h"
#include <sharedlib/networking/networking.h>
#include <yaxl.h>

using std::deque;
using std::cout;
using std::endl;
using std::map;
using std::function;

class Client;

class Master {
public:
    Master();
    virtual ~Master();
    void run(void);
    void handlePacket(Packet* packet, Client* client);

    typedef function<void(Packet*, Client*)> LambdaEvent;

private:
    int UID_counter;

    DataInterface* _dataInterface;
    deque<Client*> _clients;
    yaxl::socket::ServerSocket* _server;
    bool _isAlive;

    void onConnect(Client* client);
    void loadLambdas();
    void registerPacketEvent(PacketType type, LambdaEvent event);

    map<PacketType, LambdaEvent> _handlers;
};

#endif	/* MASTER_H */

