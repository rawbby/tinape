#pragma once

#include "./vec2.hpp"

#include <numeric.hpp>

#include <bit>

using Index = i16;
using IndexPair = Vec2<Index>;

namespace std {
template<>
struct hash<IndexPair>
{
  using result_type = u64;
  using argument_type = IndexPair;

  [[nodiscard]] result_type operator()(argument_type pair) const noexcept
  {
    return bit_cast<u32>(pair);
  }
};
}
