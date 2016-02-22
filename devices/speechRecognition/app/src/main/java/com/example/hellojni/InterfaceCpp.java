package com.example.hellojni;

public class InterfaceCpp {

    // new code
    static {
        System.loadLibrary("hello-jni");
    }

    public native String stringFromCPP();
}
