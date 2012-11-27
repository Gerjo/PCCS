#include "ISettings.h"
#include <yaxl.h>

bool ISettings::loadFromFile(string filename) {
    yaxl::file::File file(filename);

    if(file.isFile()) {
        cout << "+ Loading settings from '" << filename << "'." << endl;

        data = Data::fromJson(file.readAll());
        load();

        file.write(data.toJson(true));

        return true;
    } else {
        cout << "+ Settings file '" << filename << "' not found. Proceeding with defaults." << endl;
        return false;
    }

    return false;
}

string ISettings::getRandomNickname() {
    // A unique name, great if you run multiple clients.
    stringstream ss;
    ss << "default-" << std::fixed << phantom::Util::getTime();
   return ss.str();
}

float ISettings::load(string key, float defaultValue) {
    if(data.hasKey(key)) {
        return data(key);
    }
    return defaultValue;
}

string ISettings::load(string key, string defaultValue) {
    if(data.hasKey(key)) {
        return data(key).toString();
    }
    return defaultValue;
}

double ISettings::load(string key, double defaultValue) {
    if(data.hasKey(key)) {
        return (float) data(key);
    }
    return defaultValue;
}

int ISettings::load(string key, int defaultValue) {
    if(data.hasKey(key)) {
        return (int) data(key);
    }
    return defaultValue;
}