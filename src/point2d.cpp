#include <jni/object.hpp>
#include <jni/string_conversion.hpp>
#include <jni/types.hpp>
#include <mapbox/geometry/point.hpp>
#include <point2d.hpp>

namespace GeometryTools {

void Point2D::registerNative(jni::JNIEnv &env) {
  jni::Class<Point2D>::Singleton(env);
}

mapbox::geometry::point<int64_t>
Point2D::convert(jni::JNIEnv &env, const jni::Object<Point2D> &jPoint) {
  static auto &javaClass = jni::Class<Point2D>::Singleton(env);
  static auto xField = javaClass.GetField<jlong>(env, "x");
  static auto yField = javaClass.GetField<jlong>(env, "y");

  return {jPoint.Get(env, xField), jPoint.Get(env, yField)};
}

jni::Local<jni::Object<Point2D>>
Point2D::New(jni::JNIEnv &env, const mapbox::geometry::point<int64_t> &point) {

  static auto &javaClass = jni::Class<Point2D>::Singleton(env);
  static auto constructor =
      javaClass.GetConstructor<jni::jlong, jni::jlong>(env);

  return javaClass.New(env, constructor, static_cast<jlong>(point.x),
                       static_cast<jlong>(point.y));
}

} // namespace GeometryTools
