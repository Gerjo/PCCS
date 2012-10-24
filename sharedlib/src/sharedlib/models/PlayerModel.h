#ifndef PLAYERMODEL_H
#define	PLAYERMODEL_H

#include "../serialization/Data.h"

class PlayerModel {
public:
    int id;

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
