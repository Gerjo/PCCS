package com.pccs.main;

import java.net.Socket;
import java.util.ArrayList;


public class Terminal {
    private ArrayList<Client> clients;
    
    public Terminal() {
        clients = new ArrayList<>();
    }
    
    public synchronized void onConnect(Client client) {
        clients.add(client);
        
        ArrayList<Byte> buff = new ArrayList<>();
        
        while(client.available() > 0) {
            buff.add((byte) client.read());
        }
        
        
        byte[] meh = new byte[buff.size()];
        
        for(int i = 0; i < buff.size(); ++i) {
            meh[i] = buff.get(i);
        }
        System.out.println(new String(meh));
        
        
        client.write("HTTP/1.0 200 OK\r\n Content-Type:application/json\r\n\r\n");
        client.write("Get into the choppper!");
        client.close();
        
        System.out.println("Registrered a new connection (client).");
    }
}
