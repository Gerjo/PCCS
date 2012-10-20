#ifndef PACKETSTUFF_H
#define	PACKETSTUFF_H

#include <string>

using namespace std;



struct Packet {
public:
    enum Types {
        DEFAULT,
        WHOAREYOU,
        IAM,
        PING,
        PONG,
        
        COUNT
    };

    static const char EOT = '>';
    const int headerPrefixLength  = 7;
    const int headerPostfixLength = 1;

    static Packet* createHeader(const char* byte) {
        Packet* p = new Packet();

        p->_version  = (byte[0] && 0b11110000) >> 4;
        p->_priority = (byte[0] && 0b00001111);
        p->_type     = byte[1] | (byte[2] << 8);

        p->_payloadLength =
                byte[3]         |
                (byte[4] << 8)  |
                (byte[5] << 16) |
                (byte[6] << 24) ;

        return p;
    }

    // void init(string payload, short type, char priority, char version) {

    Packet() {
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

    int length() {
        return headerPostfixLength + headerPrefixLength + _payload.length();
    }

    const char* getBytes() {
        char* bytes = new char[length()];

        bytes[0] = ((_priority & 0b00001111) | (_version & 0b00001111) << 4);

        bytes[1] = _type;
        bytes[2] = _type >> 8;

        bytes[3] = (_payloadLength >> 0)  & 0b11111111;
        bytes[4] = (_payloadLength >> 8)  & 0b11111111;
        bytes[5] = (_payloadLength >> 16) & 0b11111111;
        bytes[6] = (_payloadLength >> 24) & 0b11111111;

        for(int i = 0; i < _payload.length(); ++i) {
            bytes[i + headerPrefixLength] = _payload.at(i);
        }

        bytes[length() - 1] = EOT;

       return bytes;
    }

    short getType() {
        return _type;
    }

    int getPayloadLength() {
        return _payloadLength;
    }

    char getPriority() {
        return _priority;
    }

    char getVersion() {
        return _version;
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