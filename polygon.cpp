#include "polygon.hpp"
#include <iostream>
#include <algorithm>
#include <iterator>

std::istream& kuznetsov::operator>>(std::istream& in, kuznetsov::Polygon& polygon)
{
  std::istream& sentry = in;
  if (!sentry) {
    return in;
  }
  int amount = 0;
  in >> amount;
  if (amount < 3) {
    in.setstate(std::ios::failbit);
    return in;
  }
  kuznetsov::Polygon tmp;
  using istr = std::istream_iterator< kuznetsov::Point >;
  std::copy_n(istr(in), amount, std::back_inserter(tmp.points));
  if (in) {
    polygon = tmp;
  }
  return in;
}

bool kuznetsov::operator==(const kuznetsov::Polygon& p1, const kuznetsov::Polygon& p2)
{
  return p1.points == p2.points;
}

