#include <wagyu.hpp>


extern "C" JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *) {
    jni::JNIEnv& env { jni::GetEnv(*vm) };

    GeometryTools::Wagyu::registerNative(env);

    return jni::Unwrap(jni::jni_version_1_2);
}
