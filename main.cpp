#include <iostream>
#include <fstream>
#include <iterator>
#include <limits>
#include <map>
#include <functional>
#include "commands.hpp"

int main(int argv, char** argc)
{
  std::ifstream in;
  if (argv == 2) {
    in.open(argc[1]);
    if (!in.is_open()) {
      std::cerr << "Error in opening file!\n";
      return 1;
    }
  } else {
    std::cerr << "Invalid amount of arguments!\n";
    return 1;
  }

  using istr = std::istream_iterator< kuznetsov::Polygon >;
  std::vector< kuznetsov::Polygon > polygons;

  try {
    while (!in.eof()) {
      std::copy(istr(in), istr(), std::back_inserter(polygons));
      if (!in) {
        in.clear();
        in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      }
    }
  } catch (const std::exception& ex) {
    std::cerr << ex.what();
    return 1;
  }

  kuznetsov::Commands commands(std::cin, std::cout,std::move(polygons));

  std::map< std::string, std::function< void() > > commandsStorage {
    {"AREA", std::bind(&kuznetsov::Commands::getArea, std::ref(commands))},
    {"MAX", std::bind(&kuznetsov::Commands::getMax, std::ref(commands))},
    {"MIN", std::bind(&kuznetsov::Commands::getMin, std::ref(commands))},
    {"COUNT", std::bind(&kuznetsov::Commands::getCount, std::ref(commands))},
    {"MAXSEQ", std::bind(&kuznetsov::Commands::getMaxSeq, std::ref(commands))}
  };

}
