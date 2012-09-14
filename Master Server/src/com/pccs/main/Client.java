package com.pccs.main;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.util.logging.Level;
import java.util.logging.Logger;


public class Client {
    private Socket socket;
    private InputStream istream;
    private OutputStream ostream;
    
    public Client(Socket socket) {
        try {
            this.socket = socket;
            this.istream = socket.getInputStream();
            this.ostream = socket.getOutputStream();
        } catch (IOException ex) {
            System.out.println(ex);
        }
    }
    
    public int available() {
        try {
            return istream.available();
        } catch (IOException ex) {
            System.out.println(ex);
        }
        
        return -1;
    }
    
    public int read() {
        try {
            return istream.read();
        } catch (IOException ex) {
            System.out.println(ex);
        }
        
        return -1;
    }
    
    public void write(String data) {
        try {
            ostream.write(data.getBytes());
        } catch (IOException ex) {
            System.out.println(ex);
        }
    }
    
    public void close() {
        try {
            socket.close();
        } catch (IOException ex) {
            System.out.println(ex);
        }
    }
    
    public Socket getSocket() {
        return socket;
    }
    
    public InputStream getIstream() {
        return istream;
    }
    
    public OutputStream getOstream() {
        return ostream;
    }
}
