#pragma once

#include "./vec2.h"

#include <bit>
#include <cstdint>

namespace base {
using Index = std::int16_t;
using IndexPair = Vec2<Index>;
}

namespace std {
template<>
struct hash<base::IndexPair>
{
  using result_type = std::size_t;
  using argument_type = base::IndexPair;

  [[nodiscard]] result_type operator()(argument_type pair) const noexcept
  {
    return std::bit_cast<std::uint32_t>(pair);
  }
};
}
