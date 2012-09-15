package com.pccs.main;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.UnsupportedEncodingException;
import java.net.Socket;
import java.net.URLDecoder;
import java.net.URLEncoder;
import java.util.ArrayList;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.json.simple.JSONObject;


public class Client {
    private Socket socket;
    private InputStream istream;
    private OutputStream ostream;
    private StringBuilder buff;
    private MasterServer masterServer;
    
    public Client(Socket socket, MasterServer masterServer) {
        this.masterServer = masterServer;
        this.socket       = socket;
        buff              = new StringBuilder();
        
        try {
            this.istream = socket.getInputStream();
            this.ostream = socket.getOutputStream();
        } catch (IOException ex) {
            System.out.println(ex);
        }
    }
    
    public void run() {
        try {
            while(istream.available() > 0) {
                char read = (char) istream.read();
                buff.append(read);
                
                System.out.println("Read: " + read);
                
                if(read == '\n') {
                    masterServer.handleClientRequest(this);
                    buff = new StringBuilder();
                    System.out.println("Finished handling, back to reading.");
                }
            }
        } catch (IOException ex) {
            System.out.println(ex);
        }
    }
    
    public String getRequest() {
        return dataToString().trim();
    }
    
    public String dataToString() {
        try {
            return URLDecoder.decode(buff.toString(), "UTF-8");
        } catch (UnsupportedEncodingException ex) {
            return URLDecoder.decode(buff.toString());
        }
    }
    
    public void returnResponse(JSONObject json) {
        returnResponse(json.toJSONString());
    }
    
    public void returnResponse(String data) {
        try {
            
            try {
                data = URLEncoder.encode(data, "UTF-8");
            } catch (UnsupportedEncodingException ex) {
                data = URLEncoder.encode(data);
            }
            
            data += '\n';
            
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
}
