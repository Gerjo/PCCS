#ifndef SETTINGS_H_DEDICATED_SERVER
#define	SETTINGS_H_DEDICATED_SERVER

// Wrapped in a static class, later on we can load this from a
// configuration file.
class Settings {
public:

    // Seconds between "scoket.accept()" and "LETS CONNECT". This filters
    // out rogue clients such as portscanners.
    constexpr static double AUTH_GRACE_TIME = 2.0;

    // After how many times of inactivity should the player be concidered
    // disconnected? Currently this relies on PING. Lateron we can match
    // this against any valid packet received.
    constexpr static double PING_GRACE_TIME = 10.0;
};

#endif	/* SETTINGS_H_DEDICATED_SERVER */
