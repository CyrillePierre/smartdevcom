package com.example.toto.speechrecognition;

import android.content.Context;
import android.content.res.XmlResourceParser;
import android.speech.tts.Voice;

import org.xmlpull.v1.XmlPullParser;
import org.xmlpull.v1.XmlPullParserException;
import org.xmlpull.v1.XmlPullParserFactory;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

/**
 * Created by toto on 17/01/16.
 */
public class Parser {

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
                    commands.add(new VoiceCommands("", "", 0));
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

                    default :

                }

                cptText = (cptText + 1) % 3;
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
