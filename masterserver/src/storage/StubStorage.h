#ifndef STUBSTORAGE_H
#define	STUBSTORAGE_H

#include <map>
#include <phantom.h>
#include "DataInterface.h"
#include <sharedlib/serialization/Data.h>
#include <sharedlib/models/DedicatedModel.h>
#include <iostream>

using std::map;
using std::cout;
using std::endl;
using std::pair;

class StubStorage : public DataInterface {
public:
    virtual bool isKnown(const int& uid) {
        return _servers.find(uid) != _servers.end();
    }

    virtual void registerServer(DedicatedModel model) {
	cout << "new model" << endl;
    	_servers.insert(pair<const int, DedicatedModel>(model.uid, model));
        updatePing(model.uid);
    }

    virtual void updatePing(const int& uid) {
        _servers.at(uid).lastPing = phantom::Util::getTime();
    }

    virtual Data listServers() {
        Data data;

        for(pair<const int, DedicatedModel> server : _servers) {
            data("servers")(server.second.uid) = server.second.toData();
        }

        return data;
    }

private:
    map<const int, DedicatedModel> _servers;
};

#endif	/* STUBSTORAGE_H */

