
package com.pccs.main;

import java.net.ServerSocket;
import java.net.Socket;


public class Listener extends Thread {
    private int port;
    private ServerSocket socket;
    private MasterServer masterServer;
    
    public Listener(int port, MasterServer masterServer) {
        this.port         = port;
        this.masterServer = masterServer;
       
        try {
            socket = new ServerSocket(port);
        } catch (Exception ex) {
            System.out.println(ex);
        }
    }
    
    @Override
    public void run() {
        while(true) {
            try {
                Socket newSocket = socket.accept();
                Client client = new Client(newSocket, masterServer);
                
                masterServer.onConnect(client);
            } catch (Exception ex) {
                System.out.println(ex);
            }
        }
    }
}
