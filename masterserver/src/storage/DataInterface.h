/*
 * File:   DataInterface.h
 * Author: gerjo
 *
 * Created on November 15, 2012, 1:51 PM
 */

#ifndef DATAINTERFACE_H
#define	DATAINTERFACE_H

class DataInterface {
public:
    virtual void updatePing() = 0;
    virtual void listServers() = 0;
};

#endif	/* DATAINTERFACE_H */

