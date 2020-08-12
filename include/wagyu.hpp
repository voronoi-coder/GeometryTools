#include <iostream>
#include <jni/jni.hpp>
#include <jni/types.hpp>

namespace GeometryTools {

class Wagyu {

public:
  static constexpr auto Name() {
    return "com/sankuai/map/render/tilefactory/Wagyu";
  }
  static void registerNative(jni::JNIEnv &);

  Wagyu(jni::JNIEnv &) { std::cout << "Native peer initialized" << std::endl; }
  Wagyu(const Wagyu &) = delete; // noncopyable
  ~Wagyu() { std::cout << "Native peer finalized" << std::endl; }

  jni::jlong Add(jni::JNIEnv &, jni::jlong a, jni::jlong b) { return a + b; }
  jni::jlong Subtract(jni::JNIEnv &, jni::jlong a, jni::jlong b) {
    return a - b;
  }
};

} // namespace GeometryTools
