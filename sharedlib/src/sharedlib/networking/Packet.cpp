#include "Packet.h"

bool Packet::parityCheck(char parity, Packet* packet) {
    return true;
}

Packet* Packet::createHeader(const char* bytes) {
    // At least I would like to know the type: (easier for debugging)
    Packet* p = new Packet(bytes[1] | (bytes[2] << 8));

    p->_version = (bytes[0] & 0xf0) >> 4;
    p->_priority = (bytes[0] & 0xff);

    p->_payloadLength =
            ((bytes[3] & 0xff) << 0) |
            ((bytes[4] & 0xff) << 8) |
            ((bytes[5] & 0xff) << 16) |
            ((bytes[6] & 0xff) << 24);

    return p;
}

// Copy ctor for pointers:

Packet::Packet(const Packet* origin) {
    _refCount = 0;
    _payload = origin->_payload;
    _version = origin->_version;
    _priority = origin->_priority;
    _type = origin->_type;
    _payloadLength = origin->_payloadLength;
    _headerParity = origin->_headerParity;
}

Packet::Packet(void) {
    init();
}

Packet::Packet(short type) {
    init(type);
}

Packet::Packet(short type, string payload) {
    init(type, payload);
}

Packet::Packet(short type, string payload, char priority) {
    init(type, payload, priority);
}

Packet::Packet(short type, string payload, char priority, char version) {
    init(type, payload, priority, version);
}

int Packet::length(void) {
    return headerPostfixLength + headerPrefixLength + _payload.length();
}

const char* Packet::getBytes(void) {
    char* bytes = new char[length()];

    bytes[0] = ((_priority & 0xf) | (_version & 0xf0) << 4);

    bytes[1] = static_cast<char> (_type);
    bytes[2] = _type >> 8;

    bytes[3] = static_cast<char> ((_payloadLength >> 0) & 0xff);
    bytes[4] = static_cast<char> ((_payloadLength >> 8) & 0xff);
    bytes[5] = static_cast<char> ((_payloadLength >> 16) & 0xff);
    bytes[6] = static_cast<char> ((_payloadLength >> 24) & 0xff);

    for (unsigned int i = 0; i < _payload.length(); ++i) {
        bytes[i + headerPrefixLength] = _payload.at(i);
    }

    bytes[length() - 1] = EOT;

    return bytes;
}

string Packet::getPayload(void) {
    return _payload;
}

void Packet::setPayload(string payload) {
    _payload = payload;
    _payloadLength = payload.length();
}

short Packet::getType(void) {
    return _type;
}

int Packet::getPayloadLength(void) {
    return _payloadLength;
}

char Packet::getPriority(void) {
    return _priority;
}

char Packet::getVersion(void) {
    return _version;
}

string Packet::formatByte(char byte) {
    string formatted;

    char mask = 1;

    for (char i = 0; i < 8; ++i) {
        if (byte & mask) {
            formatted = "1" + formatted;
        } else {
            formatted = "0" + formatted;
        }

        if (i == 3) {
            formatted = " " + formatted;
        }

        mask <<= 1;
    }

    return formatted;
}

// Experimental, I know I could use shared_ptr, but this plays nicer
// with concurrency. The "tryPop" is an atomic operation, which returns 0
// if nothing is available. If we used shared_ptr's, we couldn't return
// 0, so the "pop" action cannot be atomic since a "size" and separate
// "pop" call is required. Any thoughts to overcome this without adding
// wrappers for the wrapper for the wrapper? -- Gerjo

void Packet::retain(void) {
    ++_refCount;
}

void Packet::release(void) {
#ifdef _DEBUG
    if (_refCount <= 0) {
        cout << "!! WARNING: Packet::release() Release called without retaining first.";
    }
#endif

    if (--_refCount <= 0) {
        delete this;
    }
}

void Packet::init(short type, string payload , char priority, char version) {
    _refCount = 0;
    _payloadLength = payload.length();
    _version = version;
    _priority = priority;
    _type = type;
    _payload = payload;
}

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