package com.example.hellojni;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.speech.tts.TextToSpeech;
import android.view.Menu;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import com.example.hellojni.json.Device;
import com.example.hellojni.json.JsonData;

import org.apache.commons.lang3.StringUtils;

import java.util.ArrayList;
import java.util.Locale;

public class MainActivity extends Activity{
    private Button btnSpeak;
    private TextToSpeech tts;

    // distance minimale entre deux phrases, pouhr savoir si elles veulent dire la même chose
    private static final int DISTANCE_MIN = 5;

    private ArrayList<VoiceCommands> commands;

    BluetoothStream bs;

    @Override
    protected void onCreate(final Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        JsonData devices = new JsonData();
        Device d = new Device("name", "activation", "totoBle", "diction", "0X04");

        devices = JsonParser.parse(getApplicationContext());
        //JsonParser.addObject2(d, getApplicationContext());

        /*try {
            JsonParser.assetToFile(getAssets().open("voiceData.json", AssetManager.ACCESS_BUFFER), getApplicationContext());
        } catch (IOException e) {
            e.printStackTrace();
        }*/

        InterfaceCpp inte = new InterfaceCpp();
        System.out.println(inte.stringFromCPP());

        btnSpeak = (Button) findViewById(R.id.button);

        tts = new TextToSpeech(this, new TextToSpeech.OnInitListener() {
            @Override
            public void onInit(int status) {
                Locale locale = new Locale("fr", "FR");

                tts.setLanguage(locale);
                tts.setPitch(1);
                tts.setSpeechRate(1);

                if(getIntent().getData() != null)
                {
                    //Log.e("data : ", getIntent().getDataString());
                    //Toast.makeText(getApplicationContext(), getIntent().getDataString(), Toast.LENGTH_SHORT);
                    manageQuery(getIntent().getDataString());
                }
            }
        });

        btnSpeak.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                manageQuery("jarvis,allume,le,sapin");
            }
        });

        bs = new BluetoothStream();

        commands = Parser.parse(getApplicationContext().getResources().getXml(R.xml.voice_data));

        TextView tv = (TextView) findViewById(R.id.distance);
        tv.setText(inte.stringFromCPP());

        /*MyService service = new MyService();
        startService(new Intent(this, MyService.class));*/
    }

    /**
     * Cette méthode permet de manager la demande faite avec la voix
     * @param query : la demande faite
     */
    private void manageQuery(String query)
    {
        // Pour deverouiller le portable
        if(query.equals("Wakeup"))
        {
            bs.sendBLE(this, (char) 0, "SDC_Lisa");

            return;
        }

        // On met en minuscule, on enlève le "jarvis" qui est déjà dans toutes les requetes, et on remplace les ',' par des ' '
        String newQuery = query.toLowerCase().replace("jarvis,", "").replaceAll(","," ");
        //String newQuery = ((EditText) findViewById(R.id.edit_text)).getText().toString();

        int minDistance = 1000, distance;
        VoiceCommands goodRequest = null;

        /*  On regarde la distance entre la requête, et l'ensemble des reqûetes dans la BDD pour trouver
            laquelle faire */
        for(VoiceCommands vc: commands)
        {
            distance = StringUtils.getLevenshteinDistance(newQuery, vc.voiceActivation);

            if(distance < minDistance)
            {
                minDistance = distance;
                goodRequest = vc;
            }
        }

        /*System.out.println("LevenshteinDistance : " + StringUtils.getLevenshteinDistance(newQuery, voiceData[0]));
        System.out.println("JaroWinklerDistance : " + StringUtils.getJaroWinklerDistance(newQuery, voiceData[0]));
        System.out.println("FuzzyDistance : " + StringUtils.getFuzzyDistance(newQuery, voiceData[0], Locale.FRENCH));
        System.out.println();*/

        // On fait la bonne requpete, s'il y en a une
        /*if(minDistance < DISTANCE_MIN)
        {
           Toast.makeText(getApplicationContext(), minDistance, Toast.LENGTH_SHORT);
           System.out.println(minDistance);
        }*/

        tts.speak(goodRequest.voiceDiction, TextToSpeech.QUEUE_FLUSH, null, null);

        bs.sendBLE(this, (char) goodRequest.bluetoothCode, goodRequest.bleName);
    }


    /**
     * Permet de manager s'il faut lock ou unlock le portable au reveil
     * @param unlocked : true s'il faut deverouiller
     */
    public void manageUnlocked(boolean unlocked)
    {
        TextView tv = (TextView) findViewById(R.id.distance);

        // S'il faut deverouiller
        if(unlocked)
           tv.setText("Je laisse verouillé");

        // S'il laisser verouiller
        else
            tv.setText("Je deverouille");
    }

    /**
     * Receiving speech input
     * */
    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    protected void onDestroy() {
        if(tts != null)
        {
            tts.stop();
            tts.shutdown();
        }

        super.onDestroy();
    }
}
