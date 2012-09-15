package com.pccs.controllers;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import org.json.simple.JSONObject;
import org.json.simple.JSONValue;

public class SocketController {
    private LauncherClient launcherClient;
    private Socket socket;
    private final Object socketMutex;
    
    public SocketController(LauncherClient launcherClient) {
        this.launcherClient = launcherClient;
        this.socketMutex    = new Object();
        this.socket         = null;
    }
    
    public void setupSocket() {
        if(socket != null) {
            return;
        }
        
        try {
            addDebugLog("Connecting to: " + 
                    launcherClient.getSettings().getHost() + ":" +
                    launcherClient.getSettings().getPort() + "..."
            );
             
            socket = new Socket(
                        launcherClient.getSettings().getHost(),
                        launcherClient.getSettings().getPort()
            );
            
            addDebugLog("   connected!");
            
        } catch (IOException ex) {
            addDebugLog(ex.toString());
            
            socket = null;
        }
    }
    
    
    public JSONObject sendAndWait(JSONObject data) {
        return sendAndWait(data.toJSONString());
    }
    
    public JSONObject sendAndWait(String data) {
        
        if(data.charAt(data.length() - 1) != '\n') {
            data += '\n';
        }
        
        synchronized(socketMutex) {
            try {
                OutputStream out   = socket.getOutputStream();
                InputStream in     = socket.getInputStream();
                
                addDebugLog("Sending " + data.getBytes().length + " bytes...");
                out.write(data.getBytes());
                addDebugLog("    sent.");
                addDebugLog("Awaiting reply...");
                
                StringBuilder buff = new StringBuilder();
                boolean isRunning  = true;
                
                while(isRunning) {
                    
                    if(in.available() > 0) {
                        char read = (char) in.read();
                        buff.append(read);
                        
                        isRunning = read != '\n';
                    }
                }
                
                addDebugLog("   received " + buff.toString().getBytes().length + " bytes. ");
                
                return parseJson(buff);
                
            } catch (IOException ex) {
                addDebugLog("   Unable to IO. Exception: ");
                addDebugLog("   " + ex.toString());
                return null;
                
            } finally {
                socketMutex.notify();
            }
        }
    }
    
    private JSONObject parseJson(StringBuilder data) {
        JSONObject json = (JSONObject) JSONValue.parse(data.toString());
        if(json == null) {
            addDebugLog("   unable to parse Json reply.");
            return null;
        } else {
            addDebugLog("   parsed Json reply.");
            return json;
        }
    }
    
    private boolean hasSocket() {
        return socket != null;
    }
    
    private void addDebugLog(String log) {
        launcherClient.addDebugLog(log);
    }
}
