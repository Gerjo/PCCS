#ifndef SERVEREXCEPTION_H
#define	SERVEREXCEPTION_H

#include <phantom.h>
#include <string>

using namespace phantom;

class ServerException : public PhantomException {
public:
    ServerException(std::string error) : PhantomException(error) {

    }
};


#endif	/* SERVEREXCEPTION_H */

