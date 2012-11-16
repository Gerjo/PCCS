#include "ServerBrowser.h"


ServerBrowser::ServerBrowser() : _repaint(false) {
    paint();
}

ServerBrowser::~ServerBrowser() {
}

void ServerBrowser::paint() {
}

void ServerBrowser::update(const phantom::Time& time) {
    if(_repaint) {
        paint();
        _repaint = false;
    }

    Composite::update(time);
}

void ServerBrowser::addActions() {

}