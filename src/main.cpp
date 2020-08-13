#include "util.hpp"
#include <wagyu.hpp>
#include <point2d.hpp>
#include <util.hpp>


extern "C" JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *) {
    jni::JNIEnv& env { jni::GetEnv(*vm) };

    GeometryTools::java::util::registerNative(env);
    GeometryTools::Point2D::registerNative(env);
    GeometryTools::Wagyu::registerNative(env);

    return jni::Unwrap(jni::jni_version_1_2);
}
