package com.pccs.main;

import java.io.BufferedInputStream;
import java.net.Socket;

public final class Downloader {
    private Socket socket;
    private GuiController guiController;
    
    public Downloader() {
        guiController = new GuiController();
        
        addDebugLog("Debug log initialized.");
        
        // Spawning the socket stuff in a threads prevents the GUI from freezing.
        new Thread(new Runnable() {
            @Override
            public void run() {
               // downloadBuilds();
            }
        }).start();
    }
    
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
    
    private void addDebugLog(String string) {
        guiController.addDebugLog(string);
    }
}
