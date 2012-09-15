package com.pccs.main;

import com.pccs.views.TabContainer;
import java.io.IOException;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JFrame;
import javax.swing.JPanel;
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
        
        new Thread(new Runnable() {

            @Override
            public void run() {
                downloadBuilds();
            }
        }).start();
    }
    
    private void downloadBuilds() {
        try {
            addDebugLog("Connecting to master server.");
            socket = new Socket("localhost", 8888);
            
            addDebugLog("Connected. Requesting available builds.");
            
            socket.getOutputStream().write("{\"builds\":true}".getBytes());
            
            
        } catch (Exception ex) {
            addDebugLog(ex.toString());
        }
    }
    
    public void addDebugLog(String string) {
        this.tabs.addDebugLog(string);
    }
}
