#ifndef SETTINGS_H_GAME
#define	SETTINGS_H_GAME

#include <string>

using std::string;

class Settings {
public:
    static void load(void);

    static string SERVER_HOST;
    static string SERVER_PORT;
    static string NICKNAME;
};

#endif	/* SETTINGS_H_GAME */
