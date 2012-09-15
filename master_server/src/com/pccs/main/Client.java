package com.pccs.main;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.util.ArrayList;
import org.json.simple.JSONObject;


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
        
        data = new ArrayList<Byte>();
    }
    
    public boolean isFinished() {
        
        String str = dataToString();
        
        if(str.endsWith("\n")) {
            return true;
        }

        return false;
    }
    
    public String getRequest() {
        return dataToString().trim();
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
        } catch (IOException ex) {
            System.out.println(ex);
        }
       
    }
    
    public void returnResponse(JSONObject json) {
        returnResponse(json.toJSONString());
    }
    
    public void returnResponse(String data) {
        try {
            data += '\n';
            ostream.write(data.getBytes());
            ostream.close();
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
