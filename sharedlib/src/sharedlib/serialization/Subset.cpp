#include "Subset.h"

Subset::Subset() : _type(SUBSET) {

}

Subset& Subset::operator=(const std::string& value) {
    _type = STRING;

    _raw = value;
}

Subset& Subset::operator=(const int& value) {
    _type = INT;

    stringstream raw;
    raw << value;
    _raw = raw.str();
}

Subset& Subset::operator=(const float& value) {
    _type = FLOAT;

    stringstream raw;
    raw << value;
    _raw = raw.str();
}

Subset::operator int() {
    return atoi(_raw.c_str());
}

Subset::operator std::string() {
    return _raw;
}

Subset::operator float() {
    return atof(_raw.c_str());
}

Subset& Subset::operator() (const std::string& key) {
    Subset& subset = _map[key];
    //subset._type = SUBSET;
    return subset;
}

Subset::iterator Subset::begin() {
    return _map.begin();
}

Subset::iterator Subset::end() {
    return _map.end();
}

bool Subset::isInt(void) {
    return _type == Type::INT;
}

bool Subset::isString(void) {
    return _type == Type::STRING;
}

bool Subset::isFloat(void) {
    return _type == Type::FLOAT;
}

bool Subset::isSubset(void) {
    return _type == Type::SUBSET;
}

std::string Subset::toString() {
    return _raw;
}

void Subset::recurseToJson(std::stringstream& ss) {
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

std::string Subset::toJson() {
    std::stringstream ss;
    recurseToJson(ss);
    return ss.str();
}