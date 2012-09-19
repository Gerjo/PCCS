#include <iostream>

#include "Game.h"

using namespace std;

#include "sockets/Sockets.h"

int main(int argc, char *argv[]) {
    
    try {
        cout << "Connecting to master server..." << endl;
        Socket socket("cis.gerardmeier.com", "8078");
        cout << "Connected. Checking for updates" << endl;
        
        OutputStream& out = socket.getOutputStream();
        InputStream& in = socket.getInputStream();
        
        out.write("{\"builds\":true}\n");

        bool isRunning = true;
        char current = 0;
        char prev    = 0;
        stringstream buff;
        do {
            
            
            int available = in.available();
            if(available > 0) {
                prev    = current;
                current = in.read();
                buff << current;
            }
            
            // Account for escaped newlines.
            isRunning = !(current == '\n' && prev != '\\');
            
        } while(isRunning);
        
        cout << " Reply from the server: " << endl;
        cout << buff.str() << endl;
        
    } catch(const SocketException& ex) {
        cout << "Unable to connect to master server." << endl;
    }
    
    
    Game game();
    
    cout << " Press any key to get free cookies." << endl;
    
    return cin.get();
}