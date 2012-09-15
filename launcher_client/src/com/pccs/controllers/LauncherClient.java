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
                
                if(root.get("error") == null) {
                    JSONObject builds = (JSONObject) root.get("builds");
                    JSONArray arr     = (JSONArray) builds.get("available");

                    guiController.getBuildsTable().loadJson(arr);
                } else {
                    addDebugLog(root.toJSONString());
                }
            }
            
        }).start();
    }

    public void addDebugLog(String string) {
        guiController.addDebugLog(string);
    }
    
    public Settings getSettings() {
        return settings;
    }

    public SocketController getSocketController() {
        return socketController;
    }
}
