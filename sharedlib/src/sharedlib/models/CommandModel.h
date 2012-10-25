#ifndef COMMANDMODEL_H
#define	COMMANDMODEL_H

#include "../serialization/Data.h"

using std::string;

class CommandModel {
public:
    string UID;


    Data toData() {
        // We can cache this?
        Data data;
        data("UID") = UID;

        return data;
    }

    static CommandModel fromData(Data& data) {
        CommandModel model;
        model.UID = data("UID");

        return model;
    }
};

#endif	/* COMMANDMODEL_H */

