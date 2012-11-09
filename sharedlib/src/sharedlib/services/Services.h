#ifndef SERVICES_H
#define	SERVICES_H

#include "../CompileConfig.h"
#include "../gameobjects/GameObject.h"
#include "IBroadcast.h"

// 'Inspired' by the service container pattern. (As demo'd by Koen
// during the XNA workshop). We're just using it as a hack though. -- Gerjo

// NB: I've added static access methods, so hopefully windows will be OK with this.
class LIBEXPORT Services {
public:
    static void broadcast(GameObject* recipient, Message<Data>* message);
    static void setBroadcast(IBroadcast* broadcast);

private:
    static IBroadcast* _broadcast;
};

#endif	/* SERVICES_H */
