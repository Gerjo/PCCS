#include "Settings.h"

#include <sharedlib/serialization/Data.h>
#include <yaxl.h>
#include <file/FileException.h>

string Settings::SERVER_HOST   = "localhost";//145.92.7.231";
string Settings::SERVER_PORT   = "8075";
string Settings::NICKNAME      = "default";

void Settings::load(void) {
    try {
        Data data = Data::fromJson(yaxl::file::File("settings.json").readAll());

        SERVER_HOST = data("serverhost").toString();
        SERVER_PORT = data("serverport").toString();
        NICKNAME    = data("nickname").toString();
    } catch (yaxl::file::FileException& e) {
        std::cout << e.what();
    }
}
