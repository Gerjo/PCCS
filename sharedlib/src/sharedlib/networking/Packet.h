#ifndef PACKETSTUFF_H
#define	PACKETSTUFF_H

#include <string>
#include "../CompileConfig.h"

using namespace std;



struct LIBEXPORT Packet {
public:

    static const char EOT = '>';
    static const int headerPrefixLength  = 7;
    static const int headerPostfixLength = 1;

    static Packet* createHeader(const char* bytes) {
        Packet* p = new Packet();

        p->_version  = (bytes[0] && 0xf0) >> 4;
        p->_priority = (bytes[0] && 0xff);
        p->_type     =  bytes[1] | (bytes[2] << 8);

        p->_payloadLength =
                ((bytes[3] & 0xff) << 0)  |
                ((bytes[4] & 0xff) << 8)  |
                ((bytes[5] & 0xff) << 16) |
                ((bytes[6] & 0xff) << 24) ;

        return p;
    }

    // void init(string payload, short type, char priority, char version) {

    Packet(void) {
        init();
    }

    Packet(short type) {
        init(type);
    }

    Packet(short type, string payload) {
        init(type, payload);
    }

    Packet(short type, string payload, char priority) {
        init(type, payload, priority);
    }

    Packet(short type, string payload, char priority, char version) {
        init(type, payload, priority, version);
    }

    int length(void) {
        return headerPostfixLength + headerPrefixLength + _payload.length();
    }

    const char* getBytes(void) {
        char* bytes = new char[length()];

        bytes[0] = ((_priority & 0xf) | (_version & 0xf0) << 4);

        bytes[1] = static_cast<char>(_type);
        bytes[2] = _type >> 8;

        bytes[3] = static_cast<char>((_payloadLength >> 0)  & 0xff);
        bytes[4] = static_cast<char>((_payloadLength >> 8)  & 0xff);
        bytes[5] = static_cast<char>((_payloadLength >> 16) & 0xff);
        bytes[6] = static_cast<char>((_payloadLength >> 24) & 0xff);

        for(unsigned int i = 0; i < _payload.length(); ++i) {
            bytes[i + headerPrefixLength] = _payload.at(i);
        }

        bytes[length() - 1] = EOT;

       return bytes;
    }

    string getPayload(void) {
        return _payload;
    }

    void setPayload(string payload) {
        _payload = payload;
        _payloadLength = payload.length();
    }

    short getType(void) {
        return _type;
    }

    int getPayloadLength(void) {
        return _payloadLength;
    }

    char getPriority(void) {
        return _priority;
    }

    char getVersion(void) {
        return _version;
    }

    static string formatByte(char byte) {
        string formatted;

        char mask = 1;

        for(char i = 0; i < 8; ++i) {
            if(byte & mask) {
                formatted = "1" + formatted;
            } else {
                formatted = "0" + formatted;
            }

            if(i == 3) {
                formatted = " " + formatted;
            }

            mask <<= 1;
        }

        return formatted;
    }
private:
    void init(short type = 0, string payload = "", char priority = 0, char version = 1) {
        _payloadLength = payload.length();
        _version       = version;
        _priority      = priority;
        _type          = type;
        _payload       = payload;
    }

    string _payload;
    char _version;
    char _priority;
    short _type;
    int _payloadLength;

    char _headerParity;
};

#endif	/* PACKETSTUFF_H */

/*

[TYPE SIZE PAYLOAD]

[1 0001 16 1 example message]

0.5B      0.5B       2B     4B     1B        nB        1B
VERSION . PRIORITY . TYPE . SIZE . HPARITY . PAYLOAD . EOT

A     (static)
BB    (usually variable, second bit usually static.)
CCCC  (highly variable)

((1A & 2B) ^ 1B) ^ (1C ^ 2C ^ 3C ^ 4C) = parity byte


SIZE = size of payload, excludes any header data and EOT.

enum MessageTypes {
    IDENT_WHOAREYOU,
    IDENT_IAM,
    IDENT_ACCEPTED,
    IDENT_REJECTED
};

1
2
4
8
16
32
64

*/