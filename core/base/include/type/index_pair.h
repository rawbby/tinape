#pragma once

#include "./index.h"
#include "./vec2.h"

#include <absl/hash/hash.h>

using IndexPair = Vec2<Index>;

struct IndexPairHash
{
  typedef std::size_t result_type;
  typedef IndexPair argument_type;
  absl::Hash<std::uint32_t> hash{};

  [[nodiscard]] constexpr inline result_type operator()(argument_type pair) const noexcept
  {
    auto h = static_cast<std::uint32_t>(pair.x);
    h <<= sizeof(Index) << 3;
    h |= pair.y;
    return hash(h);
  }
};
