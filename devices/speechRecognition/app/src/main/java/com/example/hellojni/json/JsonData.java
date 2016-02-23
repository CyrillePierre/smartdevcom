package com.example.hellojni.json;

import java.util.ArrayList;

/**
 * Created by toto on 22/02/16.
 */
public class JsonData {
    private ArrayList<SmartDevice> smartDevices = new ArrayList<>();

    public ArrayList<SmartDevice> getDevices()
    {
        return smartDevices;
    }
}
