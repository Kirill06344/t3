#ifndef DELIMITER_IO_HPP
#define DELIMITER_IO_HPP
#include <iosfwd>

namespace kuznetsov {
  struct delimiter_t {
    char symbol;
  };

std::istream& operator>>(std::istream& is, delimiter_t&& d);
}
#endif
