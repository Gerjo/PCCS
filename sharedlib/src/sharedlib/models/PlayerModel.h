#ifndef PLAYERMODEL_H
#define	PLAYERMODEL_H

#include "../serialization/Data.h"
#include "../CompileConfig.h"

class LIBEXPORT PlayerModel {
public:
    int id;
    int hasSoldiers;
    PlayerModel() : id(0), hasSoldiers(0) {

    }

    Data toData() {
        // We can cache this?
        Data data;
        data("id") = id;
        data("hasSoldiers") = hasSoldiers;
        return data;
    }

    static PlayerModel fromData(Data& data) {
        PlayerModel model;
        model.id = data("id");
        model.hasSoldiers = data("hasSoldiers");
        return model;
    }
};

#endif	/* PLAYERMODEL_H */
