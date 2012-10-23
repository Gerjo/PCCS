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

    friend std::ostream& operator<< (std::ostream& out, const Subset& t) {
        switch(t._type) {
            case INT:
                return out << t._int;
            case STRING:
                return out << t._string;
            case FLOAT:
                return out << t._float;
            case SUBSET:
                return out << "(is a subset)";
        }

        return out;
    }

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
                ss << "\"" << value.first << "\":\"" << value.second << "\"";
            }

            if(++i < size) {
                ss << ",";
            }
        }

        ss << "}";
    }

    int _int;
    std::string _string;
    float _float;

    std::map<std::string, Subset> _map;

    enum Type { INT, STRING, FLOAT, SUBSET };
    Type _type;

    std::string _raw;
};

#endif	/* VALUE_H */
