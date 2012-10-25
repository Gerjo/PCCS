#ifndef SHAREDEXCEPTION_H
#define	SHAREDEXCEPTION_H

#include <phantom.h>
#include "CompileConfig.h"

class LIBEXPORT SharedException : public phantom::PhantomException {
public:
    SharedException(std::string error) : phantom::PhantomException(error) {

    }
};


#endif	/* SHAREDEXCEPTION_H */

