package com.pccs.main;

import java.util.Date;
import org.json.simple.JSONObject;
import org.json.simple.JSONValue;


public class Main {
    public static void main(String[] args) {
        // TODO: read from file.
        JSONObject json = new JSONObject();
        
        json.put("listen-port",   8078);
        json.put("builds-dir",    "/home/gerjo/masterserver/builds/");
        json.put("download-host", "http://cis.gerardmeier.com:8079/");
        
        MasterServer masterServer = new MasterServer(new Settings(json));
        masterServer.startServer();
    }
}
