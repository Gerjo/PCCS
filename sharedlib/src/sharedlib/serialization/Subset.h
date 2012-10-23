#ifndef VALUE_H
#define	VALUE_H

#include <string>
#include <map>
#include <sstream>

// temp:
#include <iostream>

using namespace std;

class Subset {
public:
    typedef std::map<std::string, Subset>::iterator iterator;

    Subset();
    virtual ~Subset();

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

    std::string toJson() {
        std::stringstream ss;
        recurseToJson(ss);
        return ss.str();
    }

private:
    void recurseToJson(std::stringstream& ss) {
        const int size = _map.size();
        int i = 0;

        ss << "{";

        for(std::pair<const std::string, Subset>& value : _map) {
            if(value.second.isSubset()) {

                ss << "\"" << value.first << "\":";

                value.second.recurseToJson(ss);

            } else {
                ss << "\"" << value.first << "\":\"" << value.second.toString() << "\"";
            }

            if(++i < size) {
                ss << ",";
            }
        }

        ss << "}";
    }

    std::map<std::string, Subset> _map;

    enum Type { INT, STRING, FLOAT, SUBSET };
    Type _type;

    std::string _raw;
    std::stringstream* _rawss;
};

#endif	/* VALUE_H */
