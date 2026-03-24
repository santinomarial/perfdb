#pragma once
#include <cassert>
#include <stdexcept>

namespace perfdb {

#define PERFDB_DISALLOW_COPY(ClassName)          \
  ClassName(const ClassName&) = delete;          \
  ClassName& operator=(const ClassName&) = delete;

#define PERFDB_ASSERT(expr, msg)                 \
  do {                                           \
    if (!(expr)) {                               \
      throw std::runtime_error(                  \
        std::string("Assertion failed: ")        \
        + (msg) + " [" + __FILE__ + ":"          \
        + std::to_string(__LINE__) + "]");       \
    }                                            \
  } while (0)

#define UNREACHABLE(msg)                         \
  do {                                           \
    assert(false && msg);                        \
    __builtin_unreachable();                     \
  } while (0)

} // namespace perfdb
