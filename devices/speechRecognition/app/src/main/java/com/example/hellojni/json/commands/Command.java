package com.example.hellojni.json.commands;

/**
 * Created by toto on 23/02/16.
 */
public class Command {

    private String voiceActivation;
    private String voiceDiction;
    private String idAction;

    public Command(String voiceActivation, String voiceDiction, String idAction) {
        this.voiceActivation = voiceActivation;
        this.voiceDiction = voiceDiction;
        this.idAction = idAction;
    }

    public String getVoiceActivation() {
        return voiceActivation;
    }

    public String getVoiceDiction() {
        return voiceDiction;
    }

    public int getIdAction() {
        return Integer.decode(idAction);
    }
}
