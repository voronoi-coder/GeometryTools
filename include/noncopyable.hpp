#pragma once

namespace GeometryTools {

namespace util {

class noncopyable {
public:
  noncopyable(noncopyable const &) = delete;
  noncopyable &operator=(noncopyable const &) = delete;

protected:
  constexpr noncopyable() = default;
  ~noncopyable() = default;
};

} // namespace util
} // namespace GeometryTools
