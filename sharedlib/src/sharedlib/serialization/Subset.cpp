#include "Subset.h"

Subset::Subset() : _rawss(new stringstream()), _type(SUBSET) {
    //cout << "create" << endl;
}

Subset::~Subset() {
    //cout << "dell" << endl;
    //delete _rawss;
}

Subset& Subset::operator=(const std::string& value) {
    _type = STRING;

    _rawss->str("");
    *_rawss << value;
}

Subset& Subset::operator=(const int& value) {
    _type = INT;

    _rawss->str("");
    *_rawss << value;
}

Subset& Subset::operator=(const float& value) {
    _type = FLOAT;

    _rawss->str("");
    *_rawss << value;
}

Subset::operator int() {
    return atoi(_rawss->str().c_str());
}

Subset::operator std::string() {
    return _rawss->str();
}

Subset::operator float() {
    return atof(_rawss->str().c_str());
}

Subset& Subset::operator() (const std::string& key) {
    return _map[key];
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
    return _rawss->str();
}