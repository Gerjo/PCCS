package com.pccs.controllers;

import com.pccs.models.Settings;
import org.json.simple.JSONArray;
import org.json.simple.JSONObject;

public final class LauncherClient {
    private GuiController guiController;
    private SocketController socketController;
    private Settings settings;
    
    public LauncherClient(Settings settings) {
        this.settings         = settings;
        this.guiController    = new GuiController(this);
        this.socketController = new SocketController(this);
        
        setupSocket();
    }
    
    private void setupSocket() {
        new Thread(new Runnable() {

            @Override
            public void run() {
                socketController.setupSocket();
                
                JSONObject root   = socketController.sendAndWait("{\"builds\":true}");
                JSONObject builds = (JSONObject) root.get("builds");
                JSONArray arr     = (JSONArray) builds.get("available");
                
                guiController.getBuildsTable().loadJson(arr);
            }
            
        }).start();
    }
    
    /*
    private void downloadBuilds() {
        try {
            addDebugLog("Connecting to localhost:8888.");
            socket = new Socket("localhost", 8888);
            
            addDebugLog("Connected. Requesting available builds.");
            
            socket.getOutputStream().write("{\"builds\":true}\n".getBytes());
            
            BufferedInputStream stream = new BufferedInputStream(socket.getInputStream());
            StringBuilder sb = new StringBuilder();
            
            boolean isRunning = true;
            
            while(isRunning) {
                if(stream.available() > 0) {
                    char read = (char) stream.read();

                    sb.append(read);
                
                    if(read == '\n') {
                        isRunning = false;
                    }
                }
            }
            
            addDebugLog("-----------------");
            addDebugLog(sb.toString());
            
        } catch (Exception ex) {
            addDebugLog(ex.toString());
        }
    }
    */
    public void addDebugLog(String string) {
        guiController.addDebugLog(string);
    }
    
    public Settings getSettings() {
        return settings;
    }
}
