#ifndef DEDICATEDSERVERMODEL_H
#define	DEDICATEDSERVERMODEL_H

#include "../serialization/Data.h"

struct MasterCookie {
    enum Type { UNKNOWN, CLIENT, SERVER };

    MasterCookie() : session(), name(), id(-1), type(UNKNOWN) { }

    int id;
    string session;
    string name;
    MasterCookie::Type type;

    Data toData() {
        Data data;
        data("uid")  = id;
        data("name") = name;
        data("type") = static_cast<int>(type);
        return data;
    }

    static MasterCookie fromData(Data& data) {
        MasterCookie model;
        model.id   = data("uid");
        model.name = data("name").toString();
        model.type = static_cast<Type>((int)data("type"));
        return model;
    }
};

#endif	/* DEDICATEDSERVERMODEL_H */
