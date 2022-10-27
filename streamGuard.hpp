#ifndef STREAM_GUARD_HPP
#define STREAM_GUARD_HPP
#include <iosfwd>
#include <iomanip>

namespace kuznetsov {
  class StreamGuard {
    public:
    StreamGuard() = delete;
    StreamGuard(std::ios& s);
    ~StreamGuard();
    private:
    std::ios& s_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags flags_;
  };
}
#endif
