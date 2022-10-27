#include "point.hpp"
#include <cmath>
#include <iostream>
#include "delimiterIO.hpp"

std::istream& kuznetsov::operator>>(std::istream& in, kuznetsov::Point& point)
{
  std::istream& sentry = in;
  if (!sentry) {
    return in;
  }
  Point tmp{};
  in >> delimiter_t{'('} >> tmp.x >> delimiter_t{';'} >> tmp.y >> delimiter_t{')'};
  if (in) {
    point = tmp;
  }
  return in;
}

bool kuznetsov::operator==(const kuznetsov::Point& p1, const kuznetsov::Point& p2)
{
  return p1.x == p2.x && p1.y == p2.y;
}

double kuznetsov::getLength(const kuznetsov::Point& p1, const kuznetsov::Point& p2)
{
  return std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2));
}

