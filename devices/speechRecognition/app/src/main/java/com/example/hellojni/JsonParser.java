package com.example.hellojni;

import android.content.Context;

import com.example.hellojni.json.Device;
import com.example.hellojni.json.JsonData;
import com.example.hellojni.json.SmartDevice;
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

    public static final String JSON_FILE = "voiceData.json";

    public static JsonData parse(Context c)
    {
        File path = c.getFilesDir();
        File file = new File(path, JSON_FILE);
        String str = readFile(file);

        System.out.println(str.toString());

        Gson gson = new GsonBuilder().create();

        JsonData devices = gson.fromJson(str, JsonData.class);

        return devices;
    }

    public static void assetToFile(InputStream is, Context c)
    {
        String str = StreamToString(is);

        writeToFile(c, str);
    }

    public static void addObject2(Device device, Context c)
    {
        Gson gson = new Gson();

        JsonData data = parse(c);
        data.getDevices().add(new SmartDevice(device));

        String content = gson.toJson(data, JsonData.class);

        writeToFile(c, content);
    }

    private static void writeToFile(Context c, String s)
    {
        File path = c.getFilesDir();

        File file = new File(path, JSON_FILE);

        FileOutputStream stream = null;
        try {
            stream = new FileOutputStream(file);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        try {
            stream.write(s.getBytes());
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
