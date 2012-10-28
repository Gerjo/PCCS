#ifndef SETTINGS_H_GAME
#define	SETTINGS_H_GAME

#include <string>

using std::string;

class Settings {
public:
    static void load(void);

    static string SERVER_HOST;
    static string SERVER_PORT;
    static double PING_INTERVAL;
};

#endif	/* SETTINGS_H_GAME */
