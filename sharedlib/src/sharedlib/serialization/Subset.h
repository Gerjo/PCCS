#ifndef VALUE_H
#define	VALUE_H

#include <string>
#include <ostream>
#include <map>
#include <sstream>

// temp:
#include <iostream>

using namespace std;

class Subset {
public:
    typedef std::map<std::string, Subset>::iterator iterator;

    Subset();
    Subset& operator= (const std::string& value);
    Subset& operator= (const int& value);
    Subset& operator= (const float& value);
    operator int();
    operator std::string();
    operator float();
    Subset& operator() (const std::string& key);
    std::map<std::string, Subset>::iterator begin();
    std::map<std::string, Subset>::iterator end();

    bool isInt(void);
    bool isString(void);
    bool isFloat(void);
    bool isSubset(void);

    std::string toString();
    std::string toJson();

private:
    void recurseToJson(std::stringstream& ss);


    std::map<std::string, Subset> _map;

    enum Type { INT, STRING, FLOAT, SUBSET };
    Type _type;

    std::string _raw;
};

#endif	/* VALUE_H */
