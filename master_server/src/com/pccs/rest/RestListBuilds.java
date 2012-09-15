package com.pccs.rest;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;

public class RestListBuilds implements IRestEntry {

    
    @Override
    public JSONObject handle(String key, Object data) {
        if(!key.equals("builds")) {
            return null;
        }
        
        JSONObject wrapper = new JSONObject();
        JSONArray builds   = new JSONArray();

        wrapper.put("available", builds);

        // TODO: link this to Jenkins.
        builds.add(createTestBuild("Master"));
        builds.add(createTestBuild("Hotfix"));
        builds.add(createTestBuild("Unstable"));
                
        return wrapper;
    }
    
    private JSONObject createTestBuild(String name) {
        JSONObject tempBuild   = new JSONObject();
        
        tempBuild.put("name", name);
        tempBuild.put("age", 1347722656);
        tempBuild.put("size", "10Mb");
        
        return tempBuild;
    }
    
}
