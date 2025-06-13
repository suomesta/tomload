
#ifndef INTEGERS_HPP
#define INTEGERS_HPP

#include <cstdint>

using i64 = int64_t;
using u64 = uint64_t;

static_assert(sizeof(long long) == sizeof(i64), "sizeof(long long) must be 8");
static_assert(sizeof(unsigned long long) == sizeof(u64), "sizeof(unsigned long long) must be 8");

#endif  // INTEGERS_HPP
