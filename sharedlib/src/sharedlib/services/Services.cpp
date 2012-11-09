
#include "Services.h"


IBroadcast* Services::_broadcast = nullptr;

void Services::broadcast(GameObject* recipient, Message<Data>* message) {
    _broadcast->broadcast(recipient, message);
}

void Services::setBroadcast(IBroadcast* broadcast) {
    _broadcast = broadcast;
}