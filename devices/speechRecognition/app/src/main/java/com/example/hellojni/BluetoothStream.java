package com.example.hellojni;

import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothGatt;
import android.bluetooth.BluetoothGattCallback;
import android.bluetooth.BluetoothGattCharacteristic;
import android.bluetooth.BluetoothGattService;
import android.bluetooth.BluetoothManager;
import android.bluetooth.BluetoothProfile;
import android.bluetooth.le.ScanCallback;
import android.bluetooth.le.ScanResult;
import android.content.Context;
import android.content.Intent;
import android.os.Handler;
import android.util.Log;
import android.widget.TextView;

import java.nio.charset.StandardCharsets;
import java.util.List;
import java.util.Timer;
import java.util.TimerTask;

/**
 * Created by toto on 18/01/16.
 */
public class BluetoothStream
{
    private BluetoothAdapter mBluetoothAdapter;
    private BluetoothGatt mGatt;

    private Handler mHandler;
    private boolean mScanning = true;

    private Context mContext;

    private static final long SCAN_PERIOD = 8000;

    private char dataToSend;
    private String bleName;
    private MainActivity act;

    private final static int BLE_DISTANCE_UNLOCKED = -65;

    public void sendBLE(MainActivity act, char data, String bleName)
    {
        dataToSend      = data;
        this.act = act;
        this.bleName    = bleName;

        mContext = act.getApplicationContext();
        mHandler = new Handler(act.getMainLooper());

        final BluetoothManager bluetoothManager =
                (BluetoothManager) mContext.getSystemService(Context.BLUETOOTH_SERVICE);

        mBluetoothAdapter = bluetoothManager.getAdapter();

        // On active le bluetooth s'il est dispo
        if (mBluetoothAdapter == null || !mBluetoothAdapter.isEnabled()) {
            Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            act.startActivityForResult(enableBtIntent, 1);
        }

        scanLeDevice(true);
    }

    private void scanLeDevice(final boolean enable) {
        if (enable) {
            // Stops scanning after a pre-defined scan period.
            mHandler.postDelayed(new Runnable() {
                @Override
                public void run() {
                    mScanning = false;
                    mBluetoothAdapter.getBluetoothLeScanner().stopScan(mScanCallback);
                }
            }, SCAN_PERIOD);

            mScanning = true;
            mBluetoothAdapter.getBluetoothLeScanner().startScan(mScanCallback);
        } else {
            mScanning = false;
            mBluetoothAdapter.getBluetoothLeScanner().stopScan(mScanCallback);
        }
    }

    private ScanCallback mScanCallback = new ScanCallback() {
        @Override
        public void onScanResult(int callbackType, ScanResult result) {
            Log.i("callbackType", String.valueOf(callbackType));
            Log.i("result", result.toString());

            String name = result.getDevice().getName();

            

            if(name != null && name.equals("SDC_Lisa") && name.equals(bleName)) {
                //Log.e("rssi : ", rssi + "");

                act.manageUnlocked(result.getRssi() < BLE_DISTANCE_UNLOCKED);
                return;
            }

            BluetoothDevice btDevice = result.getDevice();
            connectToDevice(btDevice);
        }

        @Override
        public void onBatchScanResults(List<ScanResult> results) {
            for (ScanResult sr : results) {
                Log.i("ScanResult - Results", sr.toString());
            }
        }

        @Override
        public void onScanFailed(int errorCode) {
            Log.e("Scan Failed", "Error Code: " + errorCode);
        }
    };

    public void connectToDevice(BluetoothDevice device) {
        if (mGatt == null && device.getName().contains(bleName)) {
            mGatt = device.connectGatt(mContext, false, gattCallback);
            scanLeDevice(false);// will stop after first device detection
        }
    }

    private final BluetoothGattCallback gattCallback = new BluetoothGattCallback() {
        @Override
        public void onConnectionStateChange(BluetoothGatt gatt, int status, int newState) {
            Log.i("onConnectionStateChange", "Status: " + status);
            switch (newState) {
                case BluetoothProfile.STATE_CONNECTED:
                    Log.i("gattCallback", "STATE_CONNECTED");
                    gatt.discoverServices();
                    break;
                case BluetoothProfile.STATE_DISCONNECTED:
                    Log.e("gattCallback", "STATE_DISCONNECTED");
                    break;
                default:
                    Log.e("gattCallback", "STATE_OTHER");
            }
        }

        @Override
        public void onServicesDiscovered(BluetoothGatt gatt, int status) {
            List<BluetoothGattService> services = gatt.getServices();
            Log.i("onServicesDiscovered", services.toString());

            for(BluetoothGattService service: gatt.getServices()) {
                if (service.getUuid().toString().contains("ffe0"))
                {
                    BluetoothGattCharacteristic ch = service.getCharacteristics().get(0);

                    ch.setValue(new String(String.valueOf(dataToSend)).getBytes(StandardCharsets.UTF_8));
                    boolean b = gatt.writeCharacteristic(ch);

                    Log.e("test", "" + b);

                    //gatt.disconnect();
                }
            }
        }

        @Override
        public void onCharacteristicRead(BluetoothGatt gatt,
                                         BluetoothGattCharacteristic
                                                 characteristic, int status) {
            Log.i("onCharacteristicRead", characteristic.toString());
            /*Log.i("characteristic ", String.valueOf(characteristic.get);*/


            //characteristic.setWriteType(BluetoothGattCharacteristic.);
            boolean b = gatt.writeCharacteristic(characteristic);
            Log.e("charact : ", "" + b);

            //gatt.disconnect();
        }
    };
}
