#include "commands.hpp"
#include <string>
#include <algorithm>
#include <stdexcept>
#include <functional>
#include <numeric>
#include "streamGuard.hpp"

using namespace std::placeholders;

namespace {

  int getMaxSequence(int x, const kuznetsov::Polygon& p, const kuznetsov::Polygon& comparable, int& tmp)
  {
    if (p == comparable) {
      tmp++;
      if (tmp > x) {
        return tmp;
      }
    } else {
      tmp = 0;
    }
    return x;
  }


  double getPartOfSquare(double x, const kuznetsov::Point& p1, kuznetsov::Point& p2)
  {
    x += (p1.x + p2.x) * (p1.y - p2.y);
    p2 = p1;
    return x;
  }

  double getAreaOfPolygon(const kuznetsov::Polygon& polygon)
  {
    kuznetsov::Point point = polygon.points.at(polygon.points.size() - 1);
    auto bindFunction = std::bind(getPartOfSquare, _1, _2, point);
    double sum = std::accumulate(polygon.points.begin(), polygon.points.end(), 0.0, bindFunction);
    return std::abs(sum) / 2.0;
  }

  bool compareByArea(const kuznetsov::Polygon& x, const kuznetsov::Polygon& y)
  {
    return getAreaOfPolygon(x) < getAreaOfPolygon(y);
  }

  bool compareByVertexes(const kuznetsov::Polygon& x, const kuznetsov::Polygon& y)
  {
    return x.points.size() < y.points.size();
  }


  bool isEvenAmountOfVertexes(const kuznetsov::Polygon& polygon)
  {
    return polygon.points.size() % 2 == 0;
  }

  bool isOddAmountOfVertexes(const kuznetsov::Polygon& polygon)
  {
    return polygon.points.size() % 2 != 0;
  }

  bool isEqualAmountOfVertexes(const kuznetsov::Polygon& polygon, size_t vertexes)
  {
    return polygon.points.size() == vertexes;
  }


  double accumulateFunction(double x, const kuznetsov::Polygon& polygon)
  {
    return x + getAreaOfPolygon(polygon);
  }

  bool isLessArea(const kuznetsov::Polygon& p, const kuznetsov::Polygon& comparable)
  {
    return getAreaOfPolygon(p) < getAreaOfPolygon(comparable);
  }

}

kuznetsov::Commands::Commands(std::istream& is, std::ostream& os, std::vector< Polygon >&& polygons):
  is_(is),
  os_(os),
  polygons_(polygons)
{}

void kuznetsov::Commands::getArea()
{
  std::string parameter;
  is_ >> parameter;
  std::vector< Polygon > tmp;
  if (parameter == "EVEN") {
    std::copy_if(polygons_.begin(), polygons_.end(), std::back_inserter(tmp), isEvenAmountOfVertexes);
  } else if (parameter == "ODD") {
    std::copy_if(polygons_.begin(), polygons_.end(), std::back_inserter(tmp), isOddAmountOfVertexes);
  } else if (parameter == "MEAN") {
    if (polygons_.empty()) {
      throw std::logic_error("No polygons to calculate MEAN area!");
    }
    tmp = polygons_;
  } else {
    int num = std::stoi(parameter);
    if (num < 3) {
      throw std::logic_error("Invalid amount of vertexes!");
    }
    std::copy_if(polygons_.begin(), polygons_.end(), std::back_inserter(tmp),
                 std::bind(isEqualAmountOfVertexes, _1, num));
  }
  double res = std::accumulate(tmp.begin(), tmp.end(), 0.0, accumulateFunction);
  if (parameter == "MEAN") {
    res /= tmp.size();
  }
  kuznetsov::StreamGuard guard(os_);
  os_.precision(1);
  os_ << std::fixed << res << "\n";
}

void kuznetsov::Commands::getMax()
{
  std::string parameter;
  is_ >> parameter;
  if (polygons_.empty() || (parameter != "AREA" && parameter != "VERTEXES")) {
    throw std::logic_error("Impossible to determine the max element!");
  }
  std::vector< kuznetsov::Polygon >::iterator element;
  if (parameter == "AREA") {
    element = std::max_element(polygons_.begin(), polygons_.end(), compareByArea);
  }
  if (parameter == "VERTEXES") {
    element = std::max_element(polygons_.begin(), polygons_.end(), compareByVertexes);
  }
  kuznetsov::StreamGuard guard(os_);
  if (parameter == "AREA") {
    os_.precision(1);
    os_ << std::fixed << getAreaOfPolygon(*element) << "\n";
  } else {
    os_ << element->points.size() << "\n";
  }
}

void kuznetsov::Commands::getMin()
{
  std::string parameter;
  is_ >> parameter;
  if (polygons_.empty() || (parameter != "AREA" && parameter != "VERTEXES")) {
    throw std::logic_error("Impossible to determine the min element!");
  }
  std::vector< kuznetsov::Polygon >::iterator element;
  if (parameter == "AREA") {
    element = std::min_element(polygons_.begin(), polygons_.end(), compareByArea);
  }
  if (parameter == "VERTEXES") {
    element = std::min_element(polygons_.begin(), polygons_.end(), compareByVertexes);
  }
  kuznetsov::StreamGuard guard(os_);
  if (parameter == "AREA") {
    os_.precision(1);
    os_ << std::fixed << getAreaOfPolygon(*element) << "\n";
  } else {
    os_ << element->points.size() << "\n";
  }
}

void kuznetsov::Commands::getCount()
{
  std::string parameter;
  is_ >> parameter;
  size_t count = 0;
  if (parameter == "EVEN") {
    count = std::count_if(polygons_.begin(), polygons_.end(), isEvenAmountOfVertexes);
  } else if (parameter == "ODD") {
    count = std::count_if(polygons_.begin(), polygons_.end(), isOddAmountOfVertexes);
  } else {
    int num = std::stoi(parameter);
    if (num < 3) {
      throw std::logic_error("Invalid amount of vertexes!");
    }
    count = std::count_if(polygons_.begin(), polygons_.end(), std::bind(isEqualAmountOfVertexes, _1, num));
  }
  kuznetsov::StreamGuard guard(os_);
  os_ << count << "\n";
}

void kuznetsov::Commands::getMaxSeq()
{
  kuznetsov::Polygon comparable;
  is_ >> comparable;
  if (is_.peek() != '\n') {
    is_.setstate(std::ios::failbit);
  }
  if (!is_) {
    throw std::logic_error("<INVALID COMMAND>");
  }
  int tmp = 0;
  auto supportFunction = std::bind(getMaxSequence, _1, _2, comparable, tmp);
  kuznetsov::StreamGuard guard(os_);
  os_ << std::accumulate(polygons_.begin(), polygons_.end(), 0, supportFunction) << "\n";
}

void kuznetsov::Commands::getLessArea()
{
  kuznetsov::Polygon comparable;
  is_ >> comparable;
  if (is_.peek() != '\n') {
    is_.setstate(std::ios::failbit);
  }
  if (!is_) {
    throw std::logic_error("<INVALID COMMAND>");
  }
  int count = std::count_if(polygons_.begin(), polygons_.end(), std::bind(isLessArea, _1, comparable));
  kuznetsov::StreamGuard guard(os_);
  os_ << count << "\n";
}
