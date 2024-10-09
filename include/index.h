#pragma once

#include <memory> // std::swap, std::hash

using Index = unsigned short;

struct IndexPair
{
  Index first{};
  Index second{};

  constexpr inline bool operator==(IndexPair pair) const noexcept
  {
    return (first == pair.first) && (second == pair.second);
  }

  [[nodiscard]] constexpr inline IndexPair add(Index f, Index s) const noexcept
  {
    return { static_cast<Index>(first + f), static_cast<Index>(second + s) };
  }

  constexpr inline IndexPair& sort() noexcept
  {
    if (first > second)
      std::swap(first, second);
    return *this;
  }
};

[[maybe_unused]] [[nodiscard]] constexpr inline Index
make_index(auto value) noexcept
{
  return static_cast<Index>(value);
}

[[maybe_unused]] [[nodiscard]] constexpr inline IndexPair
make_index(auto value1, auto value2) noexcept
{
  return IndexPair{ make_index(value1), make_index(value2) };
}

[[maybe_unused]] [[nodiscard]] constexpr inline IndexPair
make_sorted_index(auto value1, auto value2) noexcept
{
  return IndexPair{ make_index(value1), make_index(value2) }.sort();
}

namespace std {
template<>
struct [[maybe_unused]] hash<IndexPair>
{
  typedef size_t result_type;
  typedef IndexPair argument_type;

  [[nodiscard]] constexpr inline result_type operator()(argument_type pair) const noexcept
  {
    return static_cast<unsigned int>(pair.first) << 16 | pair.second;
  }
};
}
