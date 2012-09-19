package com.pccs.main;

import org.json.simple.JSONObject;

public final class Settings {
    private int port;
    private String buildDir;
    private String downloadHost;
    
    public Settings(JSONObject json) {
        try {
            setPort((Integer)json.get("listen-port"));
        } catch(NumberFormatException e) {
            setPort(8078);
        }
        
        try {
            setBuildDir((String)json.get("builds-dir"));
        } catch(NumberFormatException e) {
            setBuildDir("./");
        }
        
        try {
            setDownloadHost((String)json.get("download-host"));
        } catch(NumberFormatException e) {
            setDownloadHost("http://cis.gerardmeier.com:8079/");
        }
    }

    public int getPort() {
        return port;
    }

    public void setPort(int port) {
        System.out.println("Setting port to: " + port);
        this.port = port;
    }

    public String getBuildDir() {
        return buildDir;
    }

    public void setBuildDir(String buildDir) {
        this.buildDir = buildDir;
    }

    public String getDownloadHost() {
        return downloadHost;
    }

    public void setDownloadHost(String downloadHost) {
        this.downloadHost = downloadHost;
    }
}
