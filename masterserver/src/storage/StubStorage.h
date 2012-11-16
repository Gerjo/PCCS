#ifndef STUBSTORAGE_H
#define	STUBSTORAGE_H

#include <map>
#include <phantom.h>
#include "DataInterface.h"
#include <sharedlib/models/DedicatedModel.h>

using std::map;

class StubStorage : public DataInterface {
public:
    virtual bool isKnown(const int& uid) {
	return _servers.find(uid) != _servers.end();
    }

    virtual void registerServer<DedicatedModel model) {
    	_servers.insert(std::pair<const int, DedicatedModel>(model.uid, model);
        updatePing(model);
    }

    virtual void updatePing(const int& uid) {
	_servers.at(uid).lastPing = phantom::Util::getTime();
    }

    virtual void listServers() {
	;
    }

private:
    map<const int, DedicatedModel> _servers;
};

#endif	/* STUBSTORAGE_H */

