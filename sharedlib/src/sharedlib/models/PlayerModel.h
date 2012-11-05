#ifndef PLAYERMODEL_H
#define	PLAYERMODEL_H

#include "../serialization/Data.h"
#include "../CompileConfig.h"

class LIBEXPORT PlayerModel {
public:
    int id;
    string nickname;

    PlayerModel() : id(0) {

    }

    Data toData() {
        // We can cache this?
        Data data;
        data("id") = id;

        return data;
    }

    static PlayerModel fromData(Data& data) {
        PlayerModel model;
        model.id = data("id");

        return model;
    }
};

#endif	/* PLAYERMODEL_H */
