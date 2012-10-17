#include "GtServer.h"

GtServer::GtServer() {

}

GtServer::GtServer(const GtServer& orig) {
    throw new ServerException(
            "You are not allowed to copy GtServer. "
            "Use pointers or references instead.");
}

GtServer::~GtServer() {
    
}

