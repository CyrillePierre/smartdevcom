package com.example.hellojni.json.devices;

/**
 * Created by toto on 23/02/16.
 */
public class SmartDevice {
    private Device device;

    public SmartDevice(Device device) {
        this.device = device;
    }

    public Device getDevice() {
        return device;
    }
}
