#include <mapbox/geometry/multi_polygon.hpp>
#include <mapbox/geometry/wagyu/config.hpp>
#include <pointslist.hpp>
#include <wagyu.hpp>

using namespace mapbox::geometry::wagyu;

namespace GeometryTools {

void Wagyu::registerNative(jni::JNIEnv &env) {
  // Lookup the class
  static auto &javaClass = jni::Class<Wagyu>::Singleton(env);

#define METHOD(MethodPtr, name)                                                \
  jni::MakeNativePeerMethod<decltype(MethodPtr), (MethodPtr)>(name)

  jni::RegisterNativePeer<Wagyu>(
      env, javaClass, "nativePtr", std::make_unique<Wagyu, JNIEnv &>,
      "nativeInitialize", "finalize", METHOD(&Wagyu::Add, "add"),
      METHOD(&Wagyu::Subtract, "subtract"),
      METHOD(&Wagyu::add_ring, "addRing"),
      METHOD(&Wagyu::execute, "nativeExecute"));
}

void Wagyu::add_ring(
    jni::JNIEnv &env,
    const jni::Object<java::util::List /*<Point2D>*/> &jPointList,
    jni::jint polygon_type_subject) {
  mapbox::geometry::linear_ring<int64_t> ring;

  if (jPointList) {
    auto jPointArray = java::util::List::toArray<Point2D>(env, jPointList);
    auto size = jPointArray.Length(env);
    ring.reserve(size);

    for (std::size_t i = 0; i < size; i++) {
      ring.push_back(Point2D::convert(env, jPointArray.Get(env, i)));
    }
  }

  wagyu.add_ring(ring, static_cast<mapbox::geometry::wagyu::polygon_type>(
                           polygon_type_subject));
}

jni::Local<jni::Object<java::util::List>>
Wagyu::execute(jni::JNIEnv &env, jni::jint cliptype,
               jni::jint subject_fill_type, jni::jint clip_fill_type) {

  mapbox::geometry::multi_polygon<int64_t> solution;

  wagyu.execute(static_cast<clip_type>(cliptype), solution,
                static_cast<fill_type>(subject_fill_type),
                static_cast<fill_type>(clip_fill_type));

  auto jarray =
      jni::Array<jni::Object<java::util::List>>::New(env, solution.size());

  for (size_t i = 0; i < solution.size(); i++) {
    jarray.Set(env, i, asPointsListsList(env, solution.at(i)));
  }

  return java::util::Arrays::asList(env, jarray);
}

} // namespace GeometryTools
