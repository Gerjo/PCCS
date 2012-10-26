#ifndef UID_H
#define	UID_H

#include <cstdlib>
#include <sstream>
#include <string>
#include "../CompileConfig.h"

using std::stringstream;
using std::string;

class LIBEXPORT UID {
public:
    typedef string Type; // We may use INT lateron, takes less space?

    static string generate();

private:
    static unsigned long long offset;
};

#endif	/* UID_H */
