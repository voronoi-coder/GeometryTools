#include "util.hpp"

namespace GeometryTools {
namespace java {
namespace util {

void registerNative(jni::JNIEnv &env) {
  jni::Class<Arrays>::Singleton(env);
  jni::Class<List>::Singleton(env);
  jni::Class<Set>::Singleton(env);
  jni::Class<Map>::Singleton(env);
  jni::Class<Map::Entry>::Singleton(env);
}

} // namespace util
} // namespace java
} // namespace GeometryTools
