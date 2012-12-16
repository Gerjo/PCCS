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

        exportToFile("conf/settings_export.json");
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


        LOAD(squad_max_distance_to_leaderSq, 1000000.0f);

        LOAD(helicopter_detection_range,        200000.0f);
        LOAD(helicopter_start_flying_range,     30000.0f);
        LOAD(tank_detection_range,              160000.0f);
        LOAD(tank_start_driving_range,          30000.0f);
		LOAD(mech_tank_detection_range,         160000.0f);
        LOAD(mech_tank_start_driving_range,     30000.0f);


        LOAD(pathfinding_g_cost,                1);


        LOAD(pulse_soldier_vs_soldier_speed,    50.0f);
        LOAD(pulse_soldier_vs_soldier_weight,   1.0f);
        LOAD(pulse_soldier_vs_soldier_friction, 100.0f);
        LOAD(pulse_soldier_vs_any_speed,        50.0f);
        LOAD(pulse_soldier_vs_any_weight,       1.0f);
        LOAD(pulse_soldier_vs_any_friction,     100.0f);

        LOAD(pulse_dominant_speed,              5.0f);
        LOAD(pulse_dominant_weight,             10.0f);
        LOAD(pulse_dominant_friction,           0.0f);

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


    float squad_max_distance_to_leaderSq;
    float helicopter_detection_range;
    float helicopter_start_flying_range;
    float tank_detection_range;
    float tank_start_driving_range;
    float mech_tank_detection_range;
    float mech_tank_start_driving_range;

    bool loadFromFile(string filename);
    void exportToFile(string filename);

    int pathfinding_g_cost;

    float pulse_soldier_vs_soldier_speed;
    float pulse_soldier_vs_soldier_weight;
    float pulse_soldier_vs_soldier_friction;
    float pulse_soldier_vs_any_speed;
    float pulse_soldier_vs_any_weight;
    float pulse_soldier_vs_any_friction;
    float pulse_dominant_speed;
    float pulse_dominant_weight;
    float pulse_dominant_friction;

private:
    Data data;
    Data used;

    float load(string key, float defaultValue);
    string load(string key, string defaultValue);
    double load(string key, double defaultValue);
    int load(string key, int defaultValue);
    string getRandomNickname();
};

#endif	/* ISETTINGS_H */

