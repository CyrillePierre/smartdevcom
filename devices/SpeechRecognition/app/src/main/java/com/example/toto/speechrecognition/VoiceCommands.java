package com.example.toto.speechrecognition;

/**
 * Created by toto on 17/01/16.
 * Structure de données, permettant de contenir une commande vocale
 */
public class VoiceCommands {

    public String voiceActivation; // chaine de caractère à détecter
    public String voiceDiction;    // chaine de caractère que le portable dira

    public int bluetoothCode;      // code bluetooth à envoyer sur le réseau virtuel

    /**
     *
     * @param voiceActivation   : chaine de caractère à détecter
     * @param voiceDiction      : chaine de caractère que le portable dira
     * @param bluetoothCode     : code bluetooth à envoyer sur le réseau virtuel
     */
    public VoiceCommands(String voiceActivation, String voiceDiction, int bluetoothCode)
    {
        this.voiceActivation    = voiceActivation;
        this.voiceDiction       = voiceDiction;

        this.bluetoothCode      = bluetoothCode;
    }
}
