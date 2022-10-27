#ifndef POLYGON_HPP
#define POLYGON_HPP
#include <vector>
#include "point.hpp"

namespace kuznetsov {
  struct Polygon {
    std::vector< kuznetsov::Point > points;
  };
  std::istream& operator>>(std::istream& in, Polygon& polygon);
  bool operator==(const Polygon& p1, const Polygon& p2);
}
#endif
