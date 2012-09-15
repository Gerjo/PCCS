package com.pccs.main;

import com.pccs.rest.AbstractRestEntry;
import com.pccs.rest.RestListBuilds;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.Map.Entry;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.json.simple.JSONObject;
import org.json.simple.JSONValue;



public class MasterServer extends Thread {
    private Settings settings;
    private Listener listener;
    private ArrayList<Client> clients;
    private ArrayList<AbstractRestEntry> restEntries;
    private final Object clientMutex;
    
    public MasterServer(Settings settings) {
        this.settings    = settings;
        this.clients     = new ArrayList<Client>();
        this.restEntries = new ArrayList<AbstractRestEntry>();
        this.listener    = new Listener(settings.getPort(), this);
        this.clientMutex = new Object();
        
        restEntries.add(new RestListBuilds(this));
    }
    
    public void startServer() {
        listener.start();
        this.start();
    }
    
    public synchronized void onConnect(Client client) {
        synchronized(clientMutex) {
            System.out.println("A client is ready for reading.");
            clients.add(client);
        }
    }
    
    @Override
    public void run() {
        System.out.println(" Starting master worker thread.");
        while(true) {
            synchronized(clientMutex) {
                for(Client client : clients) {
                    client.run();                    
                }
            }
            
            try {
                Thread.sleep(200);
            } catch (InterruptedException ex) {
                System.out.println(ex);
            }
        }
    }
    
    private JSONObject handleJsonRequest(JSONObject jsonRequest) {
        JSONObject jsonResponse = new JSONObject();
        
        if(jsonRequest != null) {
            Iterator<Entry> it = jsonRequest.entrySet().iterator();
            
            // For each request:
            while(it.hasNext()) {
                Entry request = it.next();
                
                String key      = (String) request.getKey();
                boolean hasRepy = false;
                
                // For each REST entry:
                for(AbstractRestEntry entry : restEntries) {
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
        
        return jsonResponse;
    }
    
    public void handleClientRequest(Client client) {
        JSONObject jsonRequest  = (JSONObject) JSONValue.parse(client.getRequest());
        JSONObject jsonResponse = handleJsonRequest(jsonRequest);
        
        client.returnResponse(jsonResponse);
    }
    
    public Settings getSettings(){
        return settings;
    }
}
