package com.pccs.rest;

import org.json.simple.JSONObject;

public interface IRestEntry {
    public JSONObject handle(String key, Object data);
}
