package com.example.hellojni.json.devices;

import java.util.ArrayList;

/**
 * Created by toto on 22/02/16.
 */
public class DevicesData {
    private ArrayList<SmartDevice> smartDevices = new ArrayList<>();

    public ArrayList<SmartDevice> getDevices()
    {
        return smartDevices;
    }
}
