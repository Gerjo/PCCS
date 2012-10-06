#ifndef GAMEEXCEPTION_H
#define	GAMEEXCEPTION_H

#include <phantom.h>
using namespace phantom;

class GameException : public PhantomException {
public:
    GameException(std::string error) : PhantomException(error) {

    }
};

#endif	/* GAMEEXCEPTION_H */

