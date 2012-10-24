#include "CommandQueue.h"

CommandQueue::CommandQueue(void) {

}

CommandQueue::~CommandQueue(void) {

}

void CommandQueue::add(Command command) {
    _mutex.lock();
    _commands.push_back(command);
    _mutex.unlock();
}

void CommandQueue::run(void) {

    if(_commands.empty()) {
        return;
    }

    _mutex.lock();

    for(Command& command : _commands) {
        command();
    }

    _commands.clear();

    _mutex.unlock();
}