#ifndef IBROADCAST_H_PCCS
#define	IBROADCAST_H_PCCS

#include <phantom.h>
#include "../CompileConfig.h"

using namespace phantom;

class GameObject;

class LIBEXPORT IBroadcast {
public:
    // Implementors must guarantee that the message will be send to ALL connected
    // players, including the originating player.
    virtual void broadcast(GameObject* recipient, Message<Data>* message) = 0;
};

#endif	/* IBROADCAST_H_PCCS */

