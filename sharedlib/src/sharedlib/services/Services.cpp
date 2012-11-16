
#include "Services.h"

ISettings Services::settings;
IBroadcast* Services::_broadcast = nullptr;

void Services::broadcast(GameObject* recipient, Message<Data>* message) {
    _broadcast->broadcast(recipient, message);
}

void Services::setBroadcast(IBroadcast* broadcast) {
    _broadcast = broadcast;
}

void Services::setSettings(ISettings argSettings) {
    settings = argSettings;
}
