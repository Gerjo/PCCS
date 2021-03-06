#include "Packet.h"

char Packet::computeParity(const char* bytes) {
    //((1A & 2B) ^ 1B) ^ (1C ^ 2C ^ 3C ^ 4C) = parity byte1

    // Since some bytes will generally have a lot of "0" bits in them, I'm
    // using a less than ordinary parity creation. This creates more unique
    // samples, but we lose the ability to apply fault correction. Should
    // the latter be required, we could simply add a 1nd fault correction byte.
    return ((bytes[0] & bytes[2]) ^ bytes[1]) ^ (bytes[3] ^ bytes[4] ^ bytes[5]) ^ bytes[6];
}

Packet* Packet::createHeader(const char* bytes) {
    // At least I would like to know the type: (easier for debugging)
    Packet* p = new Packet(
            (bytes[1] & 0xff) | ((bytes[2] & 0xff) << 8)
    );

    p->_version  = (bytes[0] & 0xf0) >> 4;
    p->_priority = (bytes[0] & 0xff);

    p->_payloadLength =
            ((bytes[3] & 0xff) <<  0) |
            ((bytes[4] & 0xff) <<  8) |
            ((bytes[5] & 0xff) << 16) |
            ((bytes[6] & 0xff) << 24);

    p->_parity = bytes[7];

    // Optional block:
    p->_timestamp =
            (((uint64_t)bytes[8]  & 0xff) <<  0) |
            (((uint64_t)bytes[9]  & 0xff) <<  8) |
            (((uint64_t)bytes[10] & 0xff) << 16) |
            (((uint64_t)bytes[11] & 0xff) << 24) |
            (((uint64_t)bytes[12] & 0xff) << 32) |
            (((uint64_t)bytes[13] & 0xff) << 40) |
            (((uint64_t)bytes[14] & 0xff) << 48) |
            (((uint64_t)bytes[15] & 0xff) << 56) ;

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

size_t Packet::length(void) {
    return headerPostfixLength + headerPrefixLength + _payload.length();
}

const char* Packet::getBytes(void) {
    char* bytes = new char[length()];

    bytes[0] = ((_priority & 0xf) | (_version & 0xf0) << 4);

    bytes[1] = static_cast<char> (_type); // & 0xff
    bytes[2] = static_cast<char> (_type >> 8);

    bytes[3] = static_cast<char> ((_payloadLength >>  0) & 0xff);
    bytes[4] = static_cast<char> ((_payloadLength >>  8) & 0xff);
    bytes[5] = static_cast<char> ((_payloadLength >> 16) & 0xff);
    bytes[6] = static_cast<char> ((_payloadLength >> 24) & 0xff);
    bytes[7] = Packet::computeParity(bytes);

    // Optional block:
    uint64_t currentTime = Packet::currentTimestamp();
    bytes[8]  = static_cast<char> ((currentTime >>  0) & 0xff);
    bytes[9]  = static_cast<char> ((currentTime >>  8) & 0xff);
    bytes[10] = static_cast<char> ((currentTime >> 16) & 0xff);
    bytes[11] = static_cast<char> ((currentTime >> 24) & 0xff);
    bytes[12] = static_cast<char> ((currentTime >> 32) & 0xff);
    bytes[13] = static_cast<char> ((currentTime >> 40) & 0xff);
    bytes[14] = static_cast<char> ((currentTime >> 48) & 0xff);
    bytes[15] = static_cast<char> ((currentTime >> 56) & 0xff);

    for (unsigned int i = 0; i < _payload.length(); ++i) {
        bytes[i + headerPrefixLength] = _payload.at(i);
    }

    bytes[length() - 1] = EOT;

    return bytes;
}

char Packet::getParity(void) {
    return _parity;
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

size_t Packet::getPayloadLength(void) {
    return _payloadLength;
}

char Packet::getPriority(void) {
    return _priority;
}

char Packet::getVersion(void) {
    return _version;
}

uint64_t Packet::getTimestamp(void) {
    return _timestamp;
}

uint64_t Packet::estimatedLatency(void) {
    // pretty naive
    return Packet::currentTimestamp() - _timestamp;
}

string Packet::formatByte(const char byte) {
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

uint64_t Packet::currentTimestamp(void) {
    double time = phantom::Util::getTime() * 1000;
    return static_cast<uint64_t>(time);
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
    _parity = 0;
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