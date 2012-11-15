#ifndef PACKETSTUFF_H
#define	PACKETSTUFF_H

#include <string>
#include "../CompileConfig.h"
#include <iostream>
#include <phantom.h>
#include "../serialization/Data.h"

using namespace std;

class LIBEXPORT Packet {
public:

    static const char EOT = '>';
    static const int headerPrefixLength  = 8 + 8;
    static const int headerPostfixLength = 1;

    static Packet* createHeader(const char* bytes);
    static char computeParity(const char* bytes);

    // Copy ctor for pointers:
    Packet(const Packet* origin);
    Packet(void);
    Packet(short type);
    Packet(short type, string payload);
    Packet(short type, Data& data);
    Packet(short type, string payload, char priority);
    Packet(short type, string payload, char priority, char version);

    int length(void);

    char getParity(void);
    const char* getBytes(void);
    string getPayload(void);
    void setPayload(string payload);
    short getType(void);
    int getPayloadLength(void);
    char getPriority(void);
    char getVersion(void);
    void retain(void);
    void release(void);
    uint64_t getTimestamp(void);
    uint64_t estimatedLatency(void);

    static string formatByte(const char byte);
    static uint64_t currentTimestamp(void);
private:
    void init(short type = 0, string payload = "", char priority = 0, char version = 1);

    string _payload;
    char _version;
    char _priority;
    short _type;
    int _payloadLength;
    char _headerParity;
    char _parity;

    uint64_t _timestamp;

    unsigned int _refCount;
};

#endif	/* PACKETSTUFF_H */
