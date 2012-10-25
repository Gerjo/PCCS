#ifndef VALUE_H
#define	VALUE_H

#include <string>
#include <ostream>
#include <map>
#include <sstream>
#include "../CompileConfig.h"

using std::string;
using std::stringstream;

class LIBEXPORT Data {
public:
    typedef std::map<std::string, Data>::iterator iterator;
    typedef std::pair<std::string, Data> KeyValue;

    Data();
    Data& operator= (const std::string& value);
    Data& operator= (const int& value);
    Data& operator= (const float& value);
    operator int();
    operator std::string();
    operator float();
    Data& operator() (const std::string& key);
    std::map<std::string, Data>::iterator begin();
    std::map<std::string, Data>::iterator end();

    bool isSubset(void);

    Data& parseJson(std::string data);
    std::string toString();
    std::string toJson();

    static Data fromJson(const std::string& json);
private:
    int recurseFromJson(const std::string& data, const unsigned int offset);
    void recurseToJson(std::stringstream& ss);

    std::map<std::string, Data> _map;

    bool _isSubset;

    std::string _raw;
};

#endif	/* VALUE_H */
