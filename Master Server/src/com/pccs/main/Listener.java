
package com.pccs.main;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.logging.Level;
import java.util.logging.Logger;


public class Listener extends Thread {
    private int port;
    private ServerSocket socket;
    private Terminal terminal;
    
    public Listener(int port, Terminal terminal) throws IOException {
        this.port     = port;
        this.terminal = terminal;
        socket        = new ServerSocket(port);
    }
    
    @Override
    public void run() {
        while(true) {
            try {
                Socket newSocket = socket.accept();
                Client client = new Client(newSocket);
                
                terminal.onConnect(client);
            } catch (IOException ex) {
                System.out.println(ex);
            }
        }
    }
}
