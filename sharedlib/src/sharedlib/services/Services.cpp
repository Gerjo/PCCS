
#include "Services.h"

ISettings *Services::_settings = nullptr;
IBroadcast* Services::_broadcast = nullptr;

void Services::broadcast(GameObject* recipient, Message<Data>* message) {
    _broadcast->broadcast(recipient, message);
}

ISettings *Services::settings() {
    if(_settings == nullptr)
        _settings = new ISettings();
    return Services::_settings;
}

void Services::setBroadcast(IBroadcast* broadcast) {
    _broadcast = broadcast;
}

void Services::setSettings(ISettings *argSettings) {
    _settings = argSettings;
}
