package com.pccs.main;

import org.json.simple.JSONObject;

public final class Settings {
    private int port;
    
    public Settings(JSONObject json) {
        try {
            setPort(Integer.parseInt((String) json.get("listen-port")));
        } catch(NumberFormatException e) {
            setPort(8888);
        }
    }

    public int getPort() {
        return port;
    }

    public void setPort(int port) {
        System.out.println("Setting port to: " + port);
        this.port = port;
    }
}
