#include "streamGuard.hpp"

kuznetsov::StreamGuard::StreamGuard(std::ios& s):
  s_(s),
  precision_(s.precision()),
  flags_(s.flags())
{}

kuznetsov::StreamGuard::~StreamGuard()
{
  s_.precision(precision_);
  s_.flags(flags_);
}
