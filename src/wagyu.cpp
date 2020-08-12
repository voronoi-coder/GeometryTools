#include <wagyu.hpp>

namespace GeometryTools {

void Wagyu::registerNative(jni::JNIEnv &env) {
  // Lookup the class
  static auto &javaClass = jni::Class<Wagyu>::Singleton(env);

#define METHOD(MethodPtr, name)                                                \
  jni::MakeNativePeerMethod<decltype(MethodPtr), (MethodPtr)>(name)

  jni::RegisterNativePeer<Wagyu>(
      env, javaClass, "nativePtr", std::make_unique<Wagyu, JNIEnv &>,
      "nativeInitialize", "finalize", METHOD(&Wagyu::Add, "add"),
      METHOD(&Wagyu::Subtract, "subtract"));
}

} // namespace GeometryTools
