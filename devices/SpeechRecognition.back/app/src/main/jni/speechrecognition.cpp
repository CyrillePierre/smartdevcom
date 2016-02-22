#include <jni.h>

extern "C" {
JNIEXPORT jstring JNICALL
        Java_com_example_hellojni_HelloJni_stringFromCPP(JNIEnv *env, jobject instance);
};

JNIEXPORT jstring JNICALL
Java_com_example_hellojni_HelloJni_stringFromCPP(JNIEnv *env, jobject instance) {

    return env->NewStringUTF("Hello from c++");
}