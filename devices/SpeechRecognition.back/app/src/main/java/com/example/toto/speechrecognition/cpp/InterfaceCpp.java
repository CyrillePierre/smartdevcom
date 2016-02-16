package com.example.toto.speechrecognition.cpp;

public class InterfaceCpp {
    // Test Driver
    public static void main(String[] args) {
        InterfaceCpp inte = new InterfaceCpp();
        System.out.println("toto");
        System.out.println(inte.stringFromCPP());
    }

    // new code
    static {
        System.loadLibrary("speechrecognition");
    }
    public native String stringFromCPP();
}
