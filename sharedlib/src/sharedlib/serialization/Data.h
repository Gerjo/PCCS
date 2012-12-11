#ifndef DATA_H_PCCS
#define	DATA_H_PCCS

#include <string>
#include <ostream>
#include <map>
#include <sstream>
#include <vector>
#include "../CompileConfig.h"

using std::string;
using std::stringstream;

class Packet;

class LIBEXPORT Data {
public:
    typedef std::map<std::string, Data>::iterator iterator;
    typedef std::pair<std::string, Data> KeyValue;

    Data();

    Data& operator= (const std::string& value);
    Data& operator= (const int& value);
    Data& operator= (const float& value);
    operator int();
    operator std::string();
    operator float();
    Data& operator() (const std::string& key);
    Data& operator() (const int& key);
    std::map<std::string, Data>::iterator begin();
    std::map<std::string, Data>::iterator end();

    bool isSubset(void);
    bool hasKey(const int& key);
    bool hasKey(const string& key);

    Data& parseJson(std::string data);
    std::string toString();
    std::string toJson(const bool& pretty = false);

    // A helper to restore the order of elements. A map cannot be sorted,
    // but a vector can be. Anyway, instead of sorting, we actually insert
    // items at the correct place, making this an "O(N)" sort algorithm.
    // TODO: perhaps data should "natively" support vectors? -- Gerjo
    template <class T>
    std::vector<T> toVector() {
        auto size = _map.size();

        std::vector<T> collection(size);

        for(KeyValue pair : _map) {
            int index = atoi(pair.first.c_str());
            collection.at(index) = static_cast<T>(pair.second);
        }

        return collection;
    }

    static Data fromJson(const std::string& json);
    static Data fromPacket(Packet* packet);
private:
    int recurseFromJson(const std::string& data, const unsigned int offset);
    void recurseToJson(std::stringstream& ss);
    void recurseToJsonPretty(std::stringstream& ss, const int depth);

    std::map<std::string, Data> _map;

    bool _isSubset;

    std::string _raw;
};

#endif	/* DATA_H_PCCS */
