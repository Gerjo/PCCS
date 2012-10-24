#ifndef SHAREDEXCEPTION_H
#define	SHAREDEXCEPTION_H

#include <phantom.h>

class SharedException : public phantom::PhantomException {
public:
    SharedException(std::string error) : phantom::PhantomException(error) {

    }
};


#endif	/* SHAREDEXCEPTION_H */

