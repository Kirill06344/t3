#ifndef POINT_HPP
#define POINT_HPP
#include <iosfwd>

namespace kuznetsov {
  struct Point {
    int x, y;
  };
  std::istream& operator>>(std::istream& in, Point& point);
  bool operator==(const Point& p1, const Point& p2);
  double getLength(const Point& p1, const Point& p2);
}
#endif

