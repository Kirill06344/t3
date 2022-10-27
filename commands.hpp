#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iosfwd>
#include <vector>
#include "polygon.hpp"

namespace kuznetsov {

  class Commands {
    public:
    Commands(std::istream& is, std::ostream& os, std::vector< Polygon>&& polygons);
    void getArea();
    void getMax();
    void getMin();
    void getCount();
    void getMaxSeq();
    void getLessArea();

    private:
    std::istream& is_;
    std::ostream& os_;
    std::vector< Polygon > polygons_;
  };

}

#endif