#include <jni/jni.hpp>
#include <mapbox/geometry/point.hpp>

namespace GeometryTools {

class Point2D {
public:
  static constexpr auto Name() {
    return "com/sankuai/map/render/geometry/Point2D";
  }
  static void registerNative(jni::JNIEnv &);

  static jni::Local<jni::Object<Point2D>>
  New(jni::JNIEnv &, const mapbox::geometry::point<int64_t> &);

  static mapbox::geometry::point<int64_t> convert(jni::JNIEnv &,
                                                  const jni::Object<Point2D> &);
};

} // namespace GeometryTools
