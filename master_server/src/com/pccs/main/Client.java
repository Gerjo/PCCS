package com.pccs.main;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
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
        String rawRequest = buff.toString();
        
        rawRequest.replaceAll("\\\n", "\n");
        
        return rawRequest.trim();
    }
    
    public void write(JSONObject json) {
        write(json.toJSONString());
    }
    
    public void write(String data) {
        
        // Escape newlines since they represent an "end of transmission". This has
        // a minor glitch. If reply ends with a slash, the newline would be escape
        // implicitly. But since we use JSON, we should be OK.
        data.replaceAll("\n", "\\\n");
        
        try {
            // Append a "end of transmission" character.
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
