package com.example.hellojni.json.devices;

/**
 * Created by toto on 22/02/16.
 */
public class Device {

    //private String deviceName;
    //private String voiceActivation;
    private String bleName;
    //private String voiceDiction;
    private String codeCommand;

    /*public Device(String deviceName, String voiceActivation, String bleName, String voiceDiction, String codeBluetooth) {
        this.deviceName = deviceName;
        this.voiceActivation = voiceActivation;
        this.bleName = bleName;
        this.voiceDiction = voiceDiction;
        this.codeBluetooth = codeBluetooth;
    }*/

    public Device(String bleName, String codeCommand) {
        this.bleName = bleName;
        this.codeCommand = codeCommand;
    }

    public String getBleName() {
        return bleName;
    }

    /*public String getDeviceName() {
        return deviceName;
    }

    public String getVoiceActivation() {
        return voiceActivation;
    }

    public String getVoiceDiction() {
        return voiceDiction;
    }*/

    public String getCodeCommand() {
        return codeCommand;
    }
}