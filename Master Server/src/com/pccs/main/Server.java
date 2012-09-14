package com.pccs.main;

import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;



public class Server {
    private Terminal terminal;
    private Listener listener;
    
    
    public Server() {
        try {
            terminal = new Terminal();
            listener = new Listener(8888, terminal);
            
            listener.start();
            
        } catch (IOException ex) {
            System.out.println(ex);
        }
    }
}
