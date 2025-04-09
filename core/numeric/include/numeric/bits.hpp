#pragma once

#include "./base.hpp"

using Bits = u8;

namespace internal {
template<typename T>
constexpr u64 type_bits_v = sizeof(T) << 3;

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
mask(IsRepr auto val)
{
  return static_cast<decltype(val)>(val & internal::mask_helper_<u, l>());
}

template<u8 u, u8 l = u - 1>
constexpr auto
mask()
{
  constexpr u64 val = 0xffffffffffffffff;
  return mask<u, l>(val);
}

/// mask_shift<8,4>(0b11111111) == 0b1111
/// mask_shift<6,4>() == 0b11
/// mask_shift<8,7>(0b11100000) == 0b1
template<u8 u, u8 l = u - 1>
constexpr auto
mask_shift(IsRepr auto val)
{
  return static_cast<decltype(val)>(mask<u, 0>(val) >> l);
}

/// set_mask<8,4>(0b00000000) == 0b11110000
/// set_mask<6,4>() == 0b00110000
/// set_mask<8>  (0b00000010) == 0b10000010
template<u8 u, u8 l = u - 1>
constexpr auto
set_bits(IsRepr auto val)
{
  return static_cast<decltype(val)>(mask<u, l>() | val);
}

template<u8 u, u8 l = u - 1>
constexpr auto
set_bits()
{
  constexpr u64 val = 0x0000000000000000;
  return set_bits<u, l>(val);
}

constexpr u8
count_right_zeros(IsRepr auto val)
{
  val = ~val;

  u8 cnt = 0;
  for (; (val & 1) == 1; val >>= 1)
    ++cnt;
  return cnt;
}
