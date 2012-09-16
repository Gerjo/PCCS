package com.pccs.models;

import java.util.Date;
import org.json.simple.JSONObject;

public class BuildModel {
    private String name;
    private long age;
    private long size;
    private String url;

    public BuildModel(JSONObject json) {
        this.name = (String) json.get("name");
        this.age  = (Long) json.get("age");
        this.size = (Long) json.get("size");
        this.url  = (String) json.get("url");
    }
    
    public boolean isInstalled() {
        return false;
    }

    public long getAge() {
        return age;
    }

    public String getName() {
        return name;
    }

    public long getSize() {
        return size;
    }
    
     public String getUrl() {
        return url;
    }
    
    // Source: http://stackoverflow.com/questions/3758606/how-to-convert-byte-size-into-human-readable-format-in-java
    public String getSizeFormated() {
        boolean si = true;
        long bytes  = getSize();
        
        int unit = si ? 1000 : 1024;
        if (bytes < unit) return bytes + " B";
        int exp = (int) (Math.log(bytes) / Math.log(unit));
        String pre = (si ? "kMGTPE" : "KMGTPE").charAt(exp-1) + (si ? "" : "i");
        return String.format("%.1f %sB", bytes / Math.pow(unit, exp), pre);
    }
    
    public String getAgeFormatted() {
        Date date = new Date();
        int delta = (int) ((date.getTime() / 1000) - getAge());

        String format;
        
        if(delta < 60) {
            format = delta + " secs";
        
        } else if(delta < 3600) {
            int mins = (int) Math.floor(delta / 60);
            
            if(mins == 1) {
                format = mins + " min";
            } else {
                format = mins + " mins";
            }
            
        } else if(delta < 86400) {
            int hours = (int) Math.floor(delta / 3600);
            if(hours == 1) {
                format = hours + " hour";
            } else {
                format = hours + " hours";
            }
        
        } else  {
            int days = (int) Math.floor(delta / 86400);
            if(days == 1) {
                format = days + " day";
            } else {
                format = days + " days";
            }
        }
        
        return format;
    }
}
