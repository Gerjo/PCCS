#ifndef UID_H
#define	UID_H

#include <cstdlib>
#include <sstream>
#include <string>

using std::stringstream;
using std::string;

class UID {
public:
    static string generate() {
        stringstream ss;

        ss << "UID" << offset++;

        return ss.str();
    }
private:
    static unsigned long long offset;
};



#endif	/* UID_H */
