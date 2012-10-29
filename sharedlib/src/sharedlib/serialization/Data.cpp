#include "Data.h"

Data::Data() : _isSubset(true) {

}

Data Data::fromJson(const std::string& json) {
    Data data;
    data.parseJson(json);

    return data;
}

Data& Data::operator=(const std::string& value) {
    _isSubset = false;
    _raw = value;

    return *this;
}

Data& Data::operator=(const int& value) {
    _isSubset = false;

    stringstream raw;
    raw << value;
    _raw = raw.str();

    return *this;
}

Data& Data::operator=(const float& value) {
    _isSubset = false;

    stringstream raw;
    raw << value;
    _raw = raw.str();

    return *this;
}

Data::operator int() {
    return atoi(_raw.c_str());
}

Data::operator std::string() {
    return _raw;
}

Data::operator float() {
    return static_cast<float>(atof(_raw.c_str()));
}

Data& Data::operator() (const std::string& key) {
    return _map[key];
}

Data::iterator Data::begin() {
    return _map.begin();
}

Data::iterator Data::end() {
    return _map.end();
}

bool Data::isSubset(void) {
    return _isSubset;
}

std::string Data::toString() {
    return _raw;
}

void Data::recurseToJson(std::stringstream& ss) {
    const int size = _map.size();
    int i = 0;

    ss << '{';

    for(std::pair<const std::string, Data>& value : _map) {

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

    ss << '}';
}

std::string Data::toJson() {
    std::stringstream ss;
    recurseToJson(ss);
    return ss.str();
}

Data& Data::parseJson(std::string data) {
    recurseFromJson(data, 0);

    return *this;
}

int Data::recurseFromJson(const std::string& data, const unsigned int offset) {
    int bufferStart = -1;
    bool hasKey     = false;
    string key;

    const char START = '{';
    const char END   = '}';
    const char QUOTE = '"';
    const char COMMA = ',';

    for(unsigned int i = offset; i < data.length(); ++i) {
        const char& c = data[i];

        if(c == START) {
            if(hasKey) {
                i      = _map[key].recurseFromJson(data, i + 1);
                hasKey = false;
            }

        } else if(c == END) {
            return i + 1;

        } else if(c == QUOTE) {
            if(bufferStart == -1) {
                bufferStart = i;

            } else {
                if(!hasKey) {
                    key       = data.substr(bufferStart + 1, i - bufferStart - 1);
                    hasKey    = true;
                } else {
                    _map[key] = data.substr(bufferStart + 1, i - bufferStart - 1);
                    hasKey    = false;
                }

                bufferStart = -1;
            }
        }
    }

    return data.length();
}