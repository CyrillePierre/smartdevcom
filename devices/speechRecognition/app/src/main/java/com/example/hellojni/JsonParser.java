package com.example.hellojni;

import android.content.Context;

import com.example.hellojni.json.commands.Command;
import com.example.hellojni.json.commands.CommandsData;
import com.example.hellojni.json.commands.VoiceCommand;
import com.example.hellojni.json.devices.Device;
import com.example.hellojni.json.devices.DevicesData;
import com.example.hellojni.json.devices.SmartDevice;
import com.google.gson.Gson;
import com.google.gson.GsonBuilder;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;

/**
 * Created by toto on 22/02/16.
 */
public class JsonParser {

    public static final String DEVICES_FILE = "smartDevices.json";
    public static final String COMMANDS_FILE = "voiceCommands.json";

    public static <T> T parse(Context c, String filename, T type)
    {
        File path = c.getFilesDir();
        File file = new File(path, filename);
        String str = readFile(file);

        System.out.println(str.toString());

        Gson gson = new GsonBuilder().create();

        T devices = (T) gson.fromJson(str, type.getClass());

        return devices;
    }

    public static void assetToFile(InputStream is, Context c, String fileName)
    {
        String str = StreamToString(is);

        writeToFile(c, str, fileName);
    }

    public static <Elem, T> void addElement(Elem element, Context c, String filename, T type)
    {
        Gson gson = new Gson();

        T data = parse(c, filename, type);

        if(data instanceof DevicesData)
            ((DevicesData) data).getDevices().add(new SmartDevice((Device)element));
        else if(data instanceof CommandsData)
            ((CommandsData) data).getCommands().add(new VoiceCommand((Command) element));

        String content = gson.toJson(data, type.getClass());

        writeToFile(c, content, filename);
    }

    private static void writeToFile(Context c, String content, String fileName)
    {
        File path = c.getFilesDir();
        File file = new File(path, fileName);

        FileOutputStream stream = null;
        try {
            stream = new FileOutputStream(file);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        try {
            stream.write(content.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            try {
                stream.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    private static String readFile(File file)
    {
        int length = (int) file.length();

        byte[] bytes = new byte[length];

        FileInputStream in = null;
        try {
            in = new FileInputStream(file);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        try {
            in.read(bytes);
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            try {
                in.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        String contents = new String(bytes);

        return contents;
    }

    private static String StreamToString(InputStream stream)
    {
        String json = "";
        try {
            int size = stream.available();
            byte[] buffer = new byte[size];
            stream.read(buffer);
            stream.close();
            json = new String(buffer, "UTF-8");
        } catch (IOException ex) {
            ex.printStackTrace();
            return null;
        }
        return json;
    }
}
