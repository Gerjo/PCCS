package com.pccs.models;

import org.json.simple.JSONObject;

public class BuildModel {
    // Stringly typed anyone?
    private String name;
    private long age;
    private String size;

    public BuildModel(JSONObject json) {
        this.name = (String) json.get("name");
        this.age  = (long)   json.get("age");
        this.size = (String) json.get("size");
    }

    public long getAge() {
        return age;
    }

    public String getName() {
        return name;
    }

    public String getSize() {
        return size;
    }
}
