#ifndef SETTINGS_H_DEDICATED_SERVER
#define	SETTINGS_H_DEDICATED_SERVER

using std::string;

// Wrapped in a static class, later on we can load this from a
// configuration file.
class Settings {
public:
    static void load(void);

    // Seconds between "scoket.accept()" and "LETS CONNECT". This filters
    // out rogue clients such as portscanners.
    static double AUTH_GRACE_TIME;

    // After how many times of inactivity should the player be concidered
    // disconnected? Currently this relies on PING. Lateron we can match
    // this against any valid packet received.
    static double PING_GRACE_TIME;

    // Should the broadcast feature send the packet to the originator as well?
    // This is great for testing. You can send messages to yourself. This
    // probably messes up gameplay though, since a client would end up syncing
    // with itself.
    static bool BROADCAST_SELF_ECHO;

    // Server always listens on 0.0.0.0 only the port can be specified
    static string LISTEN_PORT;

    static float BSP_WIDTH;
    static float BSP_HEIGHT;
    static float BSP_SMALLESTSIZE;
    static unsigned BSP_MAXCOLLISIONSPERSPACE;
};


#endif	/* SETTINGS_H_DEDICATED_SERVER */
