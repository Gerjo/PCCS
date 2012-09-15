package com.pccs.rest;

import com.pccs.main.MasterServer;
import java.io.File;
import org.json.simple.JSONArray;
import org.json.simple.JSONObject;

public class RestListBuilds extends AbstractRestEntry {

    public RestListBuilds(MasterServer masterServer) {
        super(masterServer);
    }
    
    @Override
    public JSONObject handle(String key, Object data) {
        if(!key.equals("builds")) {
            return null;
        }
        
        JSONObject wrapper = new JSONObject();
        JSONArray builds   = new JSONArray();
        wrapper.put("available", builds);
        
        String path    = masterServer.getSettings().getBuildDir();
        File dir       = new File(path);
        String[] files = dir.list();
        
        for(String fileName : files) {
            File file = new File(path + "/" + fileName);
            
            builds.add(createTestBuild(file.getName(), file.lastModified(), file.length()));
        }
        

                
        return wrapper;
    }
    
    private JSONObject createTestBuild(String name, long date, long byteSize) {
        JSONObject tempBuild   = new JSONObject();
        
        tempBuild.put("name", name);
        tempBuild.put("age",  date / 1000);
        tempBuild.put("size", byteSize);
        tempBuild.put("url", masterServer.getSettings().getDownloadHost() + "" + name);
        
        return tempBuild;
    }
    
}
