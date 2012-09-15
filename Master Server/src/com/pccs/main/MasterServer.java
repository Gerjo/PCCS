package com.pccs.main;

import com.pccs.rest.IRestEntry;
import com.pccs.rest.RestListBuilds;
import java.util.ArrayList;
import java.util.Dictionary;
import java.util.HashMap;
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
    private ArrayList<IRestEntry> restEntries;
    
    public MasterServer(Settings settings) {
        this.settings    = settings;
        this.clients     = new ArrayList<>();
        this.restEntries = new ArrayList<>();
        this.listener    = new Listener(settings.getPort(), this);
        
        restEntries.add(new RestListBuilds());
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
            
            // For each request:
            while(it.hasNext()) {
                Entry request = it.next();
                
                String key      = (String) request.getKey();
                boolean hasRepy = false;
                
                // For each REST entry:
                for(IRestEntry entry : this.restEntries) {
                    JSONObject reply = entry.handle(key, request.getValue());

                    if(reply != null) {
                        hasRepy = true;
                        jsonResponse.put(key, reply);
                    }
                }
                
                // No entry was able to handle, send a nice debug message.
                if(!hasRepy) {
                    JSONObject error = new JSONObject();
                    error.put("error", "No REST entries available to parse request.");
                    jsonResponse.put(key, error);
                }
            }

        } else {
            jsonResponse.put("error", "Unable to parse request. Are you using valid JSON?");
        }
        
        client.returnResponse(jsonResponse);
    }
}
