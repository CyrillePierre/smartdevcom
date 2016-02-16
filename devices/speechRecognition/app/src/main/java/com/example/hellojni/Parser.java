package com.example.hellojni;

import android.content.res.XmlResourceParser;
import android.util.Log;

import org.xmlpull.v1.XmlPullParser;
import org.xmlpull.v1.XmlPullParserException;

import java.io.IOException;
import java.util.ArrayList;

/**
 * Created by toto on 17/01/16.
 */
public class Parser {

    public final static int NB_ELEMENT = 4;

    /**
     * Initialisation du parseur XML
     * @param ressource : le fichier xml à parser
     */
    public static ArrayList<VoiceCommands> parse(XmlResourceParser ressource)
    {
        XmlResourceParser xrp = ressource;
        int cptText = 0, eventType = 0, cptElement = 0;

        ArrayList<VoiceCommands> commands = new ArrayList<>();

        try {
            eventType = xrp.getEventType();
        } catch (XmlPullParserException e) {
            e.printStackTrace();
        }

        while (eventType != XmlPullParser.END_DOCUMENT) {
            if(eventType == XmlPullParser.START_TAG) // Si on arrive sur une nouvelle balise XML
            {
                if(xrp.getName().equals("data")) // Si la balise est une balise 'data'
                {
                    commands.add(new VoiceCommands());
                }
            }
            else if(eventType == XmlPullParser.END_TAG) // Si on arrive à la fin d'une balise
            {
                if(xrp.getName().equals("data")) // Si la balise est une balise 'data'
                {
                    ++cptElement;
                }
            }
            else if(eventType == XmlPullParser.TEXT)
            {
                switch(cptText)
                {
                    // Premier élement = voice activation
                    case 0 :
                        commands.get(cptElement).voiceActivation = xrp.getText();
                        break;

                    // Deuxième élement = voice diction
                    case 1 :
                        commands.get(cptElement).voiceDiction = xrp.getText();
                        break;

                    // Troisième élement = code bluetooth
                    case 2 :
                        commands.get(cptElement).bluetoothCode = Integer.decode(xrp.getText());
                        break;

                    // Quatrième élement = le ble auquel il faut se co
                    case 3 :
                        commands.get(cptElement).bleName = xrp.getText();
                        break;


                    default :

                }

                cptText = (cptText + 1) % NB_ELEMENT;
            }


            try {
                eventType = xrp.next(); // On passe à l'event XML suivant
            } catch (XmlPullParserException e) {
                e.printStackTrace();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        return commands;
    }
}
