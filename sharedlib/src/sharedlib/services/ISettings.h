#ifndef ISETTINGS_H
#define	ISETTINGS_H

#include <string>
#include <sstream>
#include <utils/util.h>

using std::string;
using std::stringstream;

struct ISettings {
public:
    ISettings() {
        ping_interval            = 7.0f;
        ping_interval_master     = 10.0f;

        master_host              = "localhost";
        master_port              = 8071;

        bsp_width                = 20000;
        bsp_height               = bsp_width;
        bsp_smallestsize         = 20.0f;
        bsp_maxcollisionperspace = 50.0f;

        dedicated_port           = 8070;
        dedicated_socketbacklog  = 10;
        dedicated_auth_gracetime = 2.0;
        dedicated_ping_gracetime = ping_interval + 10.0;
        dedicated_self_echo      = false;
        dedicated_name           = "I can't configure my server.";

        tmp_dedicated_host       = "localhost";
        tmp_dedicated_port       = dedicated_port;
        tmp_nickname             = getRandomNickname();
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
};

#endif	/* ISETTINGS_H */

