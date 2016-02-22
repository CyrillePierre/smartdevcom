package com.example.hellojni;

/**
 * Created by toto on 17/01/16.
 * Structure de données, permettant de contenir une commande vocale
 */
public class VoiceCommands {

    public String voiceActivation; // chaine de caractère à détecter
    public String voiceDiction;    // chaine de caractère que le portable dira

    public int bluetoothCode;      // code bluetooth à envoyer sur le réseau virtuel

    public String bleName;         // nom du ble sur lequel il faut se co
}
