#ifndef SETTINGS_H_DEDICATED_SERVER
#define	SETTINGS_H_DEDICATED_SERVER

// Wrapped in a static class, later on we can load this from a
// configuration file.
class Settings {
public:

    // Seconds between "scoket.accept()" and "LETS CONNECT". This filters
    // out rogue clients such as portscanners.
    constexpr static double AUTH_GRACE_TIME = 1.0;
};

#endif	/* SETTINGS_H_DEDICATED_SERVER */

