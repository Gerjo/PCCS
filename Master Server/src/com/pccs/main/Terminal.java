package com.pccs.main;

import java.util.ArrayList;


public class Terminal {
    private ArrayList<Client> clients;
    
    public Terminal() {
        clients = new ArrayList<>();
    }
    
    public synchronized void onConnect(Client client) {
        clients.add(client);
        
        System.out.println("Accepted new client. Reading data:");
        
        while(true) {
            System.out.println("  * read attempt.");
            
            client.read();
            
            if(client.isFinished()) {
                handleRequest(client);
                break;
            }
        }
        
        System.out.println("  * All done. \n");
        
       // System.out.println(client.dataToString());
        
    }
    
    public void handleRequest(Client client) {
         System.out.println("  * Writing reply");
         client.returnResponse("You're good to go.");
    }
}
