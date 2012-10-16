#include <cstdlib>
#include <iostream>

#include <yaxl.h>

using namespace std;
using namespace yaxl;
using namespace socket;

int main(int argc, char** argv) {

    int port = 5555;

    ServerSocket server(port);

    cout << "Listening on " << port << " for new clients. " << endl;

    do {
        Socket* client = server.accept();

        cout << "Accepted a new client, writing a reply." << endl;

        client->getOutputStream().write("Yup, it works indeed.\n");
        delete client;

        cout << "Finished writing to client. Waiting for new connection on port " << port << endl;
    } while(true);

    return 0;
}

