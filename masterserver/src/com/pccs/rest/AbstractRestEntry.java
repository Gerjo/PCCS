package com.pccs.rest;

import com.pccs.main.MasterServer;
import org.json.simple.JSONObject;

public abstract class AbstractRestEntry {
    protected MasterServer masterServer;
    
    public AbstractRestEntry(MasterServer masterServer) {
        this.masterServer = masterServer;
    }
    public abstract JSONObject handle(String key, Object data);
}
