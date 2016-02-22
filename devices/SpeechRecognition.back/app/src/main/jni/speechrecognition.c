#include <jni.h>

JNIEXPORT jstring JNICALL
Java_com_example_toto_speechrecognition_cpp_InterfaceCpp_stringFromCPP(JNIEnv *env,
                                                                       jobject instance) {
    return (*env)->NewStringUTF(env, "CA MARCHE");
}