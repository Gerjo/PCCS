#include "Subset.h"

Subset::Subset() : _type(SUBSET), _int(0), _float(0.0f), _string() {

}

Subset& Subset::operator=(const std::string& value) {
    _string = value;
    _type = STRING;

    _raw = value;
}

Subset& Subset::operator=(const int& value) {
    _int = value;
    _type = INT;

    stringstream raw;
    raw << value;
    _raw = raw.str();
}

Subset& Subset::operator=(const float& value) {
    _float = value;
    _type = FLOAT;
}

Subset::operator int() {
    return _int;
}

Subset::operator std::string() {
    return _string;
}

Subset::operator float() {
    return _float;
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
    Subset* set = this;

    std::stringstream ss;
    ss << set;
    return ss.str();
}