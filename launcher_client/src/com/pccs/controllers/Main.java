package com.pccs.controllers;

import com.pccs.models.Settings;
import java.util.Date;


public class Main {
    public static void main(String[] args) {
               
        Settings settings = new Settings("localhost", 8078);
        
        new LauncherClient(settings);
    }
}
