#include "delimiterIO.hpp"
#include <iostream>


std::istream& kuznetsov::operator>>(std::istream& is, delimiter_t&& d)
{
  std::istream::sentry sentry(is);
  if (!sentry) {
    return is;
  }
  char c = 'c';
  is >> c;
  if (is && (c != d.symbol)) {
    is.setstate(std::ios::failbit);
  }
  return is;
}
