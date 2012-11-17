#include "PacketReader.h"

PacketReader::PacketReader(yaxl::socket::InputStream& inputStream) :
        _inputStream(inputStream),
        _packet(0),
        _hasHeader(false),
        _isBlocking(false) {

}

void PacketReader::readHeader() {
    const int available = _inputStream.available();
    bool isEnsured = true;
        
    if(_isBlocking) {
        isEnsured = false;
        isEnsured = _inputStream.ensureAvailable(Packet::headerPrefixLength);
    }

    if (isEnsured && available >= Packet::headerPrefixLength) {
        string bytes = _inputStream.read(Packet::headerPrefixLength);
        _packet      = Packet::createHeader(bytes.c_str());
        _hasHeader   = true;

        char parity  = Packet::computeParity(bytes.c_str());

        if(parity != _packet->getParity()) {
            cout << "+ WARNING: Received packet parity mismatch, " << Packet::formatByte(parity) << " vs " << Packet::formatByte(_packet->getParity()) << " packet dropped." << endl;
            cout << "+ any data from this socket will probably be corrupt from now on." << endl;
            delete _packet;
            _packet    = 0;
            _hasHeader = false;
        }
    }
}

Packet* PacketReader::readPayload() {
    const int readSize = _packet->getPayloadLength() + Packet::headerPostfixLength;
    int bytesLeft      = readSize - _payload.length();
    bool isEnsured     = true;

    if(_isBlocking) {
        isEnsured = false;
        isEnsured = _inputStream.ensureAvailable(bytesLeft);
    }

    if(!isEnsured) {
        return 0;
    }

    // We'll permit two read tries:
    for (int i = 0; i < 2 && bytesLeft > 0; ++i) {
        int available = bytesLeft;

        if(!_isBlocking) {
            available = _inputStream.available();
        }

        if (available > 0) {
            int readSize = min(bytesLeft, available);
            _payload += _inputStream.read(readSize);
            bytesLeft -= readSize;
        }
    }

    if (isValid()) {
        Packet* temp = _packet;

        _payload.resize(_payload.length() - 1);
        temp->setPayload(_payload);

        // Mark internal state ready for reading a new packet.
        reset();

        return temp;
    }

    return 0;
}

void PacketReader::reset() {
    _packet    = 0;
    _hasHeader = false;
    _payload.clear();
}

bool PacketReader::isValid() {
    if (_payload.length() - Packet::headerPostfixLength == _packet->getPayloadLength()) {
        if (_payload.length() < 1 || _payload.at(_payload.length() - 1) != Packet::EOT) {
            cout << "WARNING! Packet declined, payload is less than 1 or EOT mismatch." << endl;
            cout << "Type: " << _packet->getType() << endl;
            cout << "Prio: " << _packet->getPriority() << endl;
            cout << "Version: " << _packet->getVersion() << endl;
            cout << "Payload Size: " << _packet->getPayloadLength() << endl;

            //cout << "Dumping the first 6 bytes: " << endl;
            //for(unsigned int i = 0; i < bytes.length(); ++i) {
            //    cout << i << ": " << Packet::formatByte(bytes.at(i)) << endl;
            //}

            delete _packet;
            _packet = 0;
            reset();

            return false;
        }

        return true;
    }

    return false;
}

Packet* PacketReader::readNext(void) {

    if (!_hasHeader) {
        readHeader();
    }

    if (_hasHeader) {
        return readPayload();
    }

    return 0;
}

void PacketReader::setBlocking(bool isBlocking) {
    _isBlocking = isBlocking;
    _inputStream.setBlocking(isBlocking);
}