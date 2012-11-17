#ifndef DEDICATEDSERVERMODEL_H
#define	DEDICATEDSERVERMODEL_H

#include "../serialization/Data.h"

struct DedicatedModel {

    DedicatedModel() : uid(-1), lastPing(0.0), port(0) { }

    int uid;
    string session;
    string name;
    int port;
    string ipv4;

    // Intentionally not synced over network:
    double lastPing;

    Data toData() {
        Data data;
        data("uid")  = uid;
        data("name") = name;
        data("port") = port;
        data("ipv4") = ipv4;

        return data;
    }

    static DedicatedModel fromData(Data& data) {
        DedicatedModel model;
        model.uid  = data("uid");
        model.name = data("name").toString();
        model.port = data("port");
        model.ipv4 = data("ipv4").toString();

        return model;
    }
};

#endif	/* DEDICATEDSERVERMODEL_H */
