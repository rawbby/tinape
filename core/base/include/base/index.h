#pragma once

#include "./vec2.h"

#include <absl/hash/hash.h>

#include <cstdint>

namespace base {
using Index = std::int16_t;
using IndexPair = Vec2<Index>;
}

namespace std {
template<>
struct hash<base::IndexPair>
{
  typedef std::size_t result_type;
  typedef base::IndexPair argument_type;

  [[nodiscard]] inline result_type operator()(argument_type pair) const noexcept
  {
    return std::bit_cast<std::uint32_t>(pair);
  }
};
}
