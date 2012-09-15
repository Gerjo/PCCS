package com.pccs.main;

import com.pccs.views.TabContainer;
import java.io.BufferedInputStream;
import java.net.Socket;
import javax.swing.JFrame;
import javax.swing.UIManager;

public final class Downloader {
    private JFrame window;
    private TabContainer tabs;
    private Socket socket;
    
    public Downloader() {
        try {
            UIManager.setLookAndFeel(
                UIManager.getSystemLookAndFeelClassName());
        } catch (Exception ex) {
            System.out.println(ex);
        }
        
        tabs   = new TabContainer();
        window = new JFrame("Guerrilla Tactics downloader.");
        window.getContentPane().add(tabs);

        window.setSize(400, 350);
        window.setResizable(false);
        window.setVisible(true);
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        
        addDebugLog("Debug log initialized.");
        
        // Spawning the socket stuff in a threads prevents the GUI from freezing.
        new Thread(new Runnable() {
            @Override
            public void run() {
                downloadBuilds();
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
    
    public void addDebugLog(String string) {
        tabs.addDebugLog(string);
    }
}
