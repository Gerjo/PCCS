package com.pccs.main;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.util.ArrayList;
import java.util.logging.Level;
import java.util.logging.Logger;


public class Client {
    private Socket socket;
    private InputStream istream;
    private OutputStream ostream;
    private ArrayList<Byte> data;
    
    public Client(Socket socket) {
        try {
            this.socket  = socket;
            this.istream = socket.getInputStream();
            this.ostream = socket.getOutputStream();
        } catch (IOException ex) {
            System.out.println(ex);
        }
        
        data = new ArrayList<>();
    }
    
    public boolean isFinished() {
        
        String str = dataToString();
        
        // Proper browser request:
        if(str.endsWith("\r\n\r\n")) {
            return true;
        }
 
        // Netcat, telnet or some other client:
        if(str.endsWith("\n\n")) {
            return true;
        }

        return false;
    }
    // response << "HTTP/1.0 200 OK\r\n";
    // response << "Content-Type: application/json\r\n\r\n";
    
    public String getRequest() {
        return "available_downloads";
    }
    
    public String dataToString() {
        byte[] byteArray = new byte[data.size()];
           
        for(int i = 0; i < data.size(); ++i) {
            byteArray[i] = data.get(i);
        }
        
        return new String(byteArray);
    }
    
    public void read() {
        try {
           while(istream.available() > 0) {
               data.add((byte) istream.read());
           }
        } catch (Exception ex) {
            System.out.println(ex);
        }
    }
    
    public void returnResponse(String data) {
        String header = "HTTP/1.0 200 OK\r\nContent-Type: application/json\r\n\r\n";
        
        try {
            ostream.write(header.getBytes());
            ostream.write(data.getBytes());
            close();
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
