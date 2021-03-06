#include "Data.h"
#include "../networking/Packet.h"

Data::Data() : _isSubset(true) {

}

Data Data::fromJson(const std::string& json) {
    Data data;
    data.parseJson(json);

    return data;
}

Data Data::fromPacket(Packet* packet) {
    return Data::fromJson(packet->getPayload());
}

Data& Data::operator=(const std::string& value) {
    _isSubset = false;
    _raw = value;

    return *this;
}

Data& Data::operator=(const int& value) {
    _isSubset = false;
    _raw      = std::to_string(value);

    return *this;
}

Data& Data::operator=(const float& value) {
    _isSubset = false;

    stringstream ss;
    ss.precision(99);
    ss << value;
    _raw = std::move(ss.str());

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

Data& Data::operator() (const int& key) {
    return _map[std::to_string(key)];
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

bool Data::hasKey(const int& key) {
    return hasKey(std::to_string(key));
}

bool Data::hasKey(const string& key) {
    return _map.find(key) != _map.end();
}

void Data::recurseToJson(std::stringstream& ss) {
    const size_t size = _map.size();
    size_t i = 0;

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

void Data::recurseToJsonPretty(std::stringstream& ss, const int depth) {
    const size_t size = _map.size();
    size_t i = 0;

    string padding; padding.assign((1 + depth) * 4, ' ');
    string smalli; smalli.assign(depth * 4, ' ');

    ss << smalli << "{\n";

    for(std::pair<const std::string, Data>& value : _map) {
        ss << padding;

        if(value.second.isSubset()) {

            ss << "\"" << value.first << "\": ";

            value.second.recurseToJsonPretty(ss, depth + 1);

        } else {
            ss << "\"" << value.first << "\": \"" << value.second.toString() << "\"";
        }

        if(++i < size) {
            ss << ",\n";
        }
    }

    ss << smalli << "\n}\n";
}

std::string Data::toJson(const bool& pretty) {
    std::stringstream ss;

    if(pretty) {
        recurseToJsonPretty(ss, 0);
    } else {
        recurseToJson(ss);
    }

    return ss.str();
}

Data& Data::parseJson(std::string data) {
    recurseFromJson(data, 0);

    return *this;
}

size_t Data::recurseFromJson(const std::string& data, const unsigned int offset) {
    size_t bufferStart = -1;
    bool hasKey     = false;
    string key;

    const char START  = '{';
    const char END    = '}';
    const char QUOTE  = '"';
    const char COMMA  = ',';
    const char ESCAPE = '\\';

    for(size_t i = offset; i < data.length(); ++i) {
        const char& c = data[i];

        if(c == START) {
            if(hasKey) {
                i      = _map[key].recurseFromJson(data, i + 1);
                hasKey = false;
            }

        } else if(c == END) {
            // I can't explain why the +1 here is not required. I *guess* we're
            // specifying an offset somewhere else, too. Anyway, rest assured,
            // I've written specific unit-tests to make sure this bug does
            // not reappear in the future. -- Gerjo

            //return i + 1; // <-- code I expected to work.

            return i; // <-- code that actually works.

        } else if(c == QUOTE) {
            if(i > 0) {
                // The quote was prefixed with an escaped character.
                // EG: \" <-- quote doesn't count.
                if(data[i - 1] == ESCAPE) {

                    // Make sure the escape character, wasn't escaped.
                    // EG: \\" <-- quote does count!
                    if(i >= 1 && data[i - 2] != ESCAPE) { // T
                        continue;
                    }
                }
            }

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