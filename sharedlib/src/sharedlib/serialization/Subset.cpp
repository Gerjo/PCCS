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

    ss << '{';

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

    ss << '}';
}

std::string Subset::toJson() {
    std::stringstream ss;
    recurseToJson(ss);
    return ss.str();
}

Subset& Subset::parseJson(std::string data) {
    recurseFromJson(data);

    return *this;
}

int Subset::recurseFromJson(std::string& data, int offset) {
    bool entered    = false;
    int bufferStart = -1;
    bool hasKey     = false;
    string key;

    const char START = '{';
    const char END   = '}';
    const char QUOTE = '"';
    const char COMMA = ',';

    for(int i = offset; i < data.length(); ++i) {
        char& c = data[i];

        if(c == START) {
            if(entered) {
                if(!hasKey) {
                    cout << "ehhh?" <<  endl;
                } else {
                    Subset& val = _map[key];
                    i = val.recurseFromJson(data, i + 1) + 1;
                }
            }

            entered = true;
        } else if(c == END) {
            return i;

        //} else if(c == COMMA) {
            // ignore.

        } else if(c == QUOTE) {
            if(bufferStart == -1) {
                bufferStart = i;
            } else {
                if(!hasKey) {
                    key         = data.substr(bufferStart + 1, i - bufferStart - 1);
                    hasKey      = true;
                    bufferStart = -1;

                    cout << "key " << key << endl;
                } else {
                    string value = data.substr(bufferStart + 1, i - bufferStart - 1);
                    bufferStart  = -1;
                    hasKey       = false;

                    cout << "value: " << value << endl;

                    _map[key] = value;
                }
            }
        }

      //  cout << c << endl;

    }

    return data.length();
}