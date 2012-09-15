package com.pccs.main;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.Map;
import java.util.Map.Entry;
import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.JSONValue;



public class MasterServer {
    private Settings settings;
    private Listener listener;
    private ArrayList<Client> clients;
    
    public MasterServer(Settings settings) {
        this.settings = settings;
        this.clients  = new ArrayList<>();
        this.listener = new Listener(settings.getPort(), this);
    }
    
    public void startServer() {
        listener.start();
    }
    
    
    public synchronized void onConnect(Client client) {
        clients.add(client);
        
        System.out.println("Accepted new client. Reading data:");
        
        while(true) {            
            client.read();
            
            if(client.isFinished()) {
                handleClientRequest(client);
                break;
            }
        }
        
        System.out.println("  * All done. \n");
    }
    
    public void handleClientRequest(Client client) {
        JSONObject jsonRequest  = (JSONObject) JSONValue.parse(client.getRequest());
        JSONObject jsonResponse = new JSONObject();
        
        if(jsonRequest != null) {
            Iterator<Entry> it = jsonRequest.entrySet().iterator();

            for(Entry request = it.next(); it.hasNext(); request = it.next()) {
                String key       = (String) request.getKey();
                JSONObject reply = handle(key, request.getValue());
                
                jsonResponse.put(key, reply);
            }
            
        } else {
            jsonResponse.put("error", "Unable to parse request. Are you using valid JSON?");
        }
        
        client.returnResponse(jsonResponse);
    }
    
    // TODO: move to its own class.
    private JSONObject handle(String key, Object data) {
        
        JSONObject wrapper = new JSONObject();
        
        switch(key) {
            case "builds":
                JSONArray builds = new JSONArray();
                JSONObject build = new JSONObject();
                
                wrapper.put("version", 1);
                wrapper.put("builds", builds);
                
                build.put("name", "hotfix");
                build.put("date", "07-nov-87");
                 
                builds.add(build);
                break;
                
            default:
                wrapper.put("error", "Requested key not found.");
                break;
        }
        
        
        return wrapper;
    }
}
