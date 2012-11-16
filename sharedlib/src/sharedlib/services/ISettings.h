#ifndef ISETTINGS_H
#define	ISETTINGS_H

#include <string>
#include <iostream>
#include <sstream>
#include <utils/util.h>
#include "sharedlib/serialization/Data.h"

using std::string;
using std::stringstream;
using std::cout;
using std::endl;

#define LOAD(a,b) a=load(#a,b);

struct ISettings {
public:
    ISettings() {
        load();
    }

    void load(void) {
        LOAD(ping_interval,              7.0f)
        LOAD(ping_interval_master,       10.0f)

        LOAD(master_host,                "localhost")
        LOAD(master_port,                8071)

        LOAD(bsp_width,                  20000.0f);
        LOAD(bsp_height,                 20000.0f);
        LOAD(bsp_smallestsize,           20.0f);
        LOAD(bsp_maxcollisionperspace,   50.0f);

        LOAD(dedicated_port,             8070);
        LOAD(dedicated_socketbacklog,    10);
        LOAD(dedicated_auth_gracetime,   2.0);
        LOAD(dedicated_ping_gracetime,   ping_interval + 10.0);
        LOAD(dedicated_name,             "I can't configure my server.");

        LOAD(tmp_dedicated_host,         "localhost");
        LOAD(tmp_dedicated_port,         dedicated_port);
        LOAD(tmp_nickname,               getRandomNickname());

        // Data has no boolean support *sigh*
        dedicated_self_echo = false;
    }

    float load(string key, float defaultValue) {
        if(data.hasKey(key)) {
            return data(key);
        }
        return defaultValue;
    }

    string load(string key, string defaultValue) {
        if(data.hasKey(key)) {
            return data(key).toString();
        }
        return defaultValue;
    }

    double load(string key, double defaultValue) {
        if(data.hasKey(key)) {
            return (float) data(key);
        }
        return defaultValue;
    }

    int load(string key, int defaultValue) {
        if(data.hasKey(key)) {
            return (int) data(key);
        }
        return defaultValue;
    }

    bool loadFromFile(string filename);
    string getRandomNickname();

    double ping_interval;           // Between client and dedicated.
    double ping_interval_master;    // Between anyone and master.

    string master_host;             // Listening host of the master.
    int master_port;                // Listening port of the master.

    // Binary space partitioning memory hogg tree.
    float bsp_width;
    float bsp_height;
    float bsp_smallestsize;
    float bsp_maxcollisionperspace;

    int dedicated_port;              // Listinging port of the dedicated server.
    int dedicated_socketbacklog;     // Maximum pending accept connections in the kernel.
    double dedicated_auth_gracetime; // How much time a client has to authenticate.
    double dedicated_ping_gracetime; // Time permitted between pings before forced disconnect.
    bool dedicated_self_echo;        // Broadcast messages back to the originator.
    string dedicated_name;           // Name and slogan of the server.

    // Temp stuff, this will eventually move to other places:
    string tmp_dedicated_host;
    int tmp_dedicated_port;
    string tmp_nickname;

private:
    Data data;
};

#endif	/* ISETTINGS_H */

