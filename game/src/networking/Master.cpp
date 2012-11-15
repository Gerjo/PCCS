#include "Master.h"

Master::Master(Game& game) : _game(game) {

}

Master::~Master(void) {

}

void Master::init(void) {
    connect("localhost", 8071);
}

void Master::onConnectionSuccess(void) {
    cout << "connected to master." << endl;
}

void Master::onConnectionFail(const yaxl::socket::SocketException& ex) {
    cout << ex.what() << endl;
}
