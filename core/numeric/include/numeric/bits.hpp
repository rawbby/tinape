#pragma once

#include "./base.hpp"

namespace numeric {

using Bits = u8;

namespace internal {
template<u8 u, u8 l>
constexpr u64
mask_helper_()
{
  static_assert(u >= l);
  constexpr auto m = ~static_cast<u64>(0);
  constexpr auto um = m >> (static_cast<u8>(64) - u);
  constexpr auto lm = m << l;
  return um & lm;
}
}

/// mask<8,4>(0b11111111) == 0b11110000
/// mask<6,4>() == 0b00110000
/// mask<8>(0b11111111) == 0b10000000
template<u8 u, u8 l = u - 1>
constexpr auto
mask(u64 val = 0xffffffffffffffff)
{
  return val & internal::mask_helper_<u, l>();
}

/// mask_shift<8,4>(0b11111111) == 0b1111
/// mask_shift<6,4>() == 0b11
/// mask_shift<8,7>(0b11100000) == 0b1
template<u8 u, u8 l = u - 1>
constexpr auto
mask_shift(u64 val)
{
  return mask<u, 0>(val) >> l;
}

/// set_mask<8,4>(0b00000000) == 0b11110000
/// set_mask<6,4>() == 0b00110000
/// set_mask<8>  (0b00000010) == 0b10000010
template<u8 u, u8 l = u - 1>
constexpr auto
set_bits(u64 val = 0x0000000000000000)
{
  return mask<u, l>() | val;
}

constexpr auto
count_right_zeros(u64 val)
{
  u8 cnt = 0;
  for (; (val & 1) == 0; val >>= 1)
    ++cnt;
  return cnt;
}

}
