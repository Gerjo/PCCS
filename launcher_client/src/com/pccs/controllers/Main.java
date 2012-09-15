package com.pccs.controllers;

import com.pccs.models.Settings;


public class Main {
    public static void main(String[] args) {
        
        Settings settings = new Settings("localhost", 8888);
        
        new LauncherClient(settings);
    }
}
