#include "Subset.h"

Subset::Subset() : _isSubset(true) {

}

Subset& Subset::operator=(const std::string& value) {
    _isSubset = false;
    _raw = value;
}

Subset& Subset::operator=(const int& value) {
    _isSubset = false;

    stringstream raw;
    raw << value;
    _raw = raw.str();
}

Subset& Subset::operator=(const float& value) {
    _isSubset = false;

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
    return _map[key];
}

Subset::iterator Subset::begin() {
    return _map.begin();
}

Subset::iterator Subset::end() {
    return _map.end();
}

bool Subset::isSubset(void) {
    return _isSubset;
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