package com.pccs.models;

import java.io.*;
import org.json.simple.JSONObject;
import org.json.simple.JSONValue;

public class Settings {
    private String host;
    private int port;

    public Settings() {
        
    }
    
    public Settings(JSONObject json) {
        fromJson(json);
    }
    
    public void loadDefaults() {
        host = "cis.gerardmeier.com";
        port = 8078;
    }
    
    private void fromJson(JSONObject json) {
        port = (int) (long) json.get("port");
        host = (String) json.get("host");
    }
    
    private JSONObject toJson() {
        JSONObject json = new JSONObject();
        
        json.put("port", port);
        json.put("host", host);
        
        return json;
    }
    
    public void toFile(File file) {
        
        try {
            if(!file.exists()) {
                file.createNewFile();
            }
            
            FileWriter out = new FileWriter(file);
            out.write(toJson().toJSONString());
            out.close();
            
        } catch (IOException ex) {
            System.out.println(ex);
            
        }
    }
    
    public boolean fromFile(File file) {
        
        try {
            
            BufferedReader br  =
                        new BufferedReader(
                            new InputStreamReader(
                                new DataInputStream(
                                    new FileInputStream(file)
                                )
                           )
            );
            
            JSONObject json = (JSONObject) JSONValue.parse(br);
            
            if(json == null) {
                System.out.println("JSON file corrupted :(");
                return false;
            }
            
            fromJson(json);
            return true;
            
        } catch (IOException ex) {
            System.out.println(ex);
        }
        
        return false;
    }

    public String getHost() {
        return host;
    }

    public int getPort() {
        return port;
    }
}
