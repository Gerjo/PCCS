#ifndef DEDICATEDSERVERMODEL_H
#define	DEDICATEDSERVERMODEL_H

#include "../serialization/Data.h"

struct DedicatedModel {

    DedicatedModel() : session(), name(), uid(-1) { }

    int uid;
    string session;
    string name;

    Data toData() {
        Data data;
        data("uid")  = uid;
        data("name") = name;
        return data;
    }

    static DedicatedModel fromData(Data& data) {
        DedicatedModel model;
        model.uid  = data("uid");
        model.name = data("name").toString();
        return model;
    }
};

#endif	/* DEDICATEDSERVERMODEL_H */
