#include <cstdlib>
#include <iostream>

#include <yaxl.h>
#include <Packet.h>

#include "GameHub.h"

using namespace std;
using namespace yaxl;
using namespace socket;

void printBinary(int num) {
    deque<char> string;

    for(int flag = 1, i = 0; i < 8; ++i, flag *= 2) {
        if(num & flag) {
            string.push_front('1');
        } else {
            string.push_front('0');
        }

        if(i == 3) {
            string.push_front(' ');
        }
    }

    for(char c : string) {
        cout << c;
    }

    cout << endl;
}

int main(int argc, char** argv) {
    GameHub server;
/*

    //string payload, short type, char priority, char version

    Packet* packet = new Packet("Hello", 0, 0, 0);

    const char* bytes = packet->getBytes();

    Packet* header = Packet::createHeader(bytes);

    for(int i = 0; i < packet->length(); ++i) {
        cout << i << ": " << (int) bytes[i] << " ";
        printBinary(bytes[i]);
    }

    if(header->getType() == packet->getType()) {
        cout << "getType matches" << endl;
    }

    if(header->getPayloadLength() == packet->getPayloadLength()) {
        cout << "getPayloadLength matches" << endl;
    } else {
        cout <<  header->getPayloadLength() << "vs" << packet->getPayloadLength() << endl;
    }

    if(header->getVersion() == packet->getVersion()) {
        cout << "getVersion matches" << endl;
    }*/

    return 0;
}

