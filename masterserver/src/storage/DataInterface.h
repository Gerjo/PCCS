/*
 * File:   DataInterface.h
 * Author: gerjo
 *
 * Created on November 15, 2012, 1:51 PM
 */

#ifndef DATAINTERFACE_H
#define	DATAINTERFACE_H

#include <sharedlib/models/DedicatedModel.h>
#include <sharedlib/serialization/Data.h>

class DataInterface {
public:
    virtual bool isKnown(const int& uid) = 0;
    virtual void registerServer(DedicatedModel model) = 0;
    virtual void updatePing(const int& uid) = 0;
    virtual Data listServers() = 0;
};

#endif	/* DATAINTERFACE_H */

