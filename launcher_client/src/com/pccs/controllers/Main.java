package com.pccs.controllers;

import com.pccs.models.Settings;
import java.io.File;
import javax.swing.JOptionPane;


public class Main {
    public static void main(String[] args) {
        File file   = new File("settings.json");
        
        
        if(!file.exists()) {
            Settings settings = new Settings();
            settings.loadDefaults();
            settings.toFile(file);
        }
        
        File folder = new File("builds/");
        if(!folder.exists()) {
            folder.mkdir();
        }
        
        Settings settings = new Settings();
        settings.fromFile(file);
        new LauncherClient(settings);
    }
}
