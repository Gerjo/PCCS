#ifndef ISETTINGS_H
#define	ISETTINGS_H

#include <string>
#include <iostream>
#include <sstream>
#include <utils/util.h>
#include "sharedlib/serialization/Data.h"
#include "CompileConfig.h"

using std::string;
using std::stringstream;
using std::cout;
using std::endl;

#define LOAD(a,b) a=load(#a,b);

struct LIBEXPORT ISettings {
public:
    ISettings() {
        load();
    }

    void load(void) {
        LOAD(ping_interval,            7.0f)
        LOAD(ping_interval_master,     10.0f)

        LOAD(master_host,              "cis.k42.nl")
        LOAD(master_port,              8071)

        LOAD(bsp_width,                20000.0f);
        LOAD(bsp_height,               20000.0f);
        LOAD(bsp_smallestsize,         20.0f);
        LOAD(bsp_maxcollisionperspace, 50);

        LOAD(dedicated_port,           8070);
        LOAD(dedicated_socketbacklog,  10);
        LOAD(dedicated_auth_gracetime, 2.0);
        LOAD(dedicated_ping_gracetime, ping_interval + 10.0);
        LOAD(dedicated_name,           "I can't configure my server.");

        LOAD(tmp_dedicated_host,       "localhost");
        LOAD(tmp_dedicated_port,       dedicated_port);
        LOAD(nickname,                 getRandomNickname());

        LOAD(master_ping_gracetime, ping_interval_master + 10.0);

        // Data has no boolean support *sigh*
        dedicated_self_echo = false;
    }


    double ping_interval;           // Between client and dedicated.
    double ping_interval_master;    // Between anyone and master.
    double master_ping_gracetime;   // Time permitted between pings before forced disconnect.

    string master_host;             // Listening host of the master.
    int master_port;                // Listening port of the master.

    // Binary space partitioning memory hogg tree.
    float bsp_width;
    float bsp_height;
    float bsp_smallestsize;
    unsigned int bsp_maxcollisionperspace;

    int dedicated_port;              // Listinging port of the dedicated server.
    int dedicated_socketbacklog;     // Maximum pending accept connections in the kernel.
    double dedicated_auth_gracetime; // How much time a client has to authenticate.
    double dedicated_ping_gracetime; // Time permitted between pings before forced disconnect.
    bool dedicated_self_echo;        // Broadcast messages back to the originator.
    string dedicated_name;           // Name and slogan of the server.

    // Temp stuff, this will eventually move to other places:
    string tmp_dedicated_host;
    int tmp_dedicated_port;
    string nickname;




    bool loadFromFile(string filename);

private:
    Data data;

    float load(string key, float defaultValue);
    string load(string key, string defaultValue);
    double load(string key, double defaultValue);
    int load(string key, int defaultValue);
    string getRandomNickname();

};

#endif	/* ISETTINGS_H */

