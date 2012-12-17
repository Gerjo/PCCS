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

void ISettings::exportToFile(string filename) {
    string data = used.toJson(true);

    yaxl::file::File file(filename);
    file.createNewFile();
    file.write(data);

}

string ISettings::getRandomNickname() {
    // A unique name, great if you run multiple clients.
    stringstream ss;
    ss << "default-" << std::fixed << phantom::Util::getTime();
    return ss.str();
}

float ISettings::load(string key, float defaultValue) {
    float r = defaultValue;

    if(data.hasKey(key)) {
        r = data(key);
    }

    used(key) = r;

    return r;
}

string ISettings::load(string key, string defaultValue) {
    string r = defaultValue;

    if(data.hasKey(key)) {
        r = data(key).toString();
    }

    used(key) = r;

    return r;
}

double ISettings::load(string key, double defaultValue) {
    double r = defaultValue;

    if(data.hasKey(key)) {
        r = data(key);
    }

    used(key) = static_cast<float>(r);

    return r;
}

int ISettings::load(string key, int defaultValue) {
    int r = defaultValue;

    if(data.hasKey(key)) {
        r = data(key);
    }

    used(key) = r;

    return r;
}

char ISettings::load(string key, char defaultValue) {
    char r = defaultValue;

    if(data.hasKey(key)) {
        r = static_cast<char>(static_cast<int>(data(key)));
    }
    
    used(key) = static_cast<int>(r);

    return r;
}