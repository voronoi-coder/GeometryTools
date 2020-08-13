#include <iostream>
#include <jni/jni.hpp>
#include <jni/types.hpp>
#include <mapbox/geometry/wagyu/wagyu.hpp>
#include <util.hpp>

namespace GeometryTools {

class Wagyu {

public:
  static constexpr auto Name() {
    return "com/sankuai/map/render/tilefactory/algorithm/Wagyu";
  }
  static void registerNative(jni::JNIEnv &);

  Wagyu(jni::JNIEnv &) {}
  Wagyu(const Wagyu &) = delete; // noncopyable
  ~Wagyu() {}

  jni::jlong Add(jni::JNIEnv &, jni::jlong a, jni::jlong b) { return a + b; }
  jni::jlong Subtract(jni::JNIEnv &, jni::jlong a, jni::jlong b) {
    return a - b;
  }

  void add_ring(jni::JNIEnv &env,
                const jni::Object<java::util::List /*<Point2D>*/> &jPointList,
                jni::jint polygon_type_subject);

  jni::Local<jni::Object<java::util::List>> execute(jni::JNIEnv &env,
                                                    jni::jint clip_type,
                                                    jni::jint subject_fill_type,
                                                    jni::jint clip_fill_type);

private:
  mapbox::geometry::wagyu::wagyu<int64_t> wagyu;
};

} // namespace GeometryTools
