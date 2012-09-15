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
        JSONObject build   = new JSONObject();

        wrapper.put("version", 1);
        wrapper.put("builds", builds);

        build.put("name", "hotfix");
        build.put("date", "07-nov-87");
        builds.add(build);
                
        return wrapper;
    }
    
}
