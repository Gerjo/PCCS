package com.pccs.main;

import org.json.simple.JSONObject;
import org.json.simple.JSONValue;


public class Main {
    public static void main(String[] args) {
        
        // TODO: read from file.
        JSONObject json = (JSONObject) JSONValue.parse("{\"listen-port\":\"8888\"}");
        
        MasterServer masterServer = new MasterServer(new Settings(json));
        
        
        masterServer.startServer();
    }
}
