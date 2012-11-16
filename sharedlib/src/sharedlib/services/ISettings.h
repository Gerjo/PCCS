#ifndef ISETTINGS_H
#define	ISETTINGS_H

#include <string>

using std::string;

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
    }

    bool load(string filename) {
        return true;
    }

    double ping_interval;
    double ping_interval_master;

    string master_host;
    int master_port;

    float bsp_width;
    float bsp_height;
    float bsp_smallestsize;
    float bsp_maxcollisionperspace;
};

#endif	/* ISETTINGS_H */

