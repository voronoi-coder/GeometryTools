#include <iostream>

#include <mapbox/geometry/wagyu/wagyu.hpp>
#include <mapbox/geometry_io.hpp>

using namespace mapbox::geometry::wagyu;

int main() {

  mapbox::geometry::linear_ring<std::int64_t> ring;
  ring.push_back(mapbox::geometry::point<std::int64_t>(0, 0));
  ring.push_back(mapbox::geometry::point<std::int64_t>(1, 0));
  ring.push_back(mapbox::geometry::point<std::int64_t>(1, 1));
  ring.push_back(mapbox::geometry::point<std::int64_t>(0, 1));
  ring.push_back(mapbox::geometry::point<std::int64_t>(0, 0));

  mapbox::geometry::wagyu::wagyu<std::int64_t> wagyu;
  wagyu.add_ring(ring);

  mapbox::geometry::multi_polygon<std::int64_t> solution;
  wagyu.execute(mapbox::geometry::wagyu::clip_type_union, solution,
                mapbox::geometry::wagyu::fill_type_positive,
                mapbox::geometry::wagyu::fill_type_positive);

  std::cout << solution << std::endl;
}
