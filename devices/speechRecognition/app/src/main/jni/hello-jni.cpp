#include <jni.h>
#include <iostream>

extern "C" {
    JNIEXPORT jstring JNICALL
            Java_com_example_hellojni_InterfaceCpp_stringFromCPP(JNIEnv *env, jobject instance);
};

JNIEXPORT jstring JNICALL
Java_com_example_hellojni_InterfaceCpp_stringFromCPP(JNIEnv *env, jobject instance) {

    return env->NewStringUTF("I came from CPP code :D");
}