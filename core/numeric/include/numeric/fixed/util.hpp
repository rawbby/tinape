#pragma once

#include "../bits.hpp"
#include "../fixed.hpp"
#include "../sign.hpp"
#include "./literal.hpp"

template<Bits B, Sign S_, Bits B_, i64 P_>
constexpr Fixed<S_, B, P_ + B_ - B>
round_down(Fixed<S_, B_, P_> val)
{
  return val;
}

template<Bits B, Sign S_, Bits B_, i64 P_>
constexpr auto
round_up(Fixed<S_, B_, P_> val)
{
  auto res = Fixed<S_, B, P_ + B_ - B>{ val };
  if (B < B_)
    res.repr_ += mask<B_ - B>(val.repr_) != 0;
  return res;
}

/// similar to round_up, but assumes that
/// the value could already be round down
/// beforehand
template<Bits B, Sign S_, Bits B_, i64 P_>
constexpr auto
upper_bound(Fixed<S_, B_, P_> val)
{
  auto res = Fixed<S_, B, P_ + B_ - B>{ val };
  res.repr_ += 1;
  return res;
}

/// alias the round_down
template<Bits B, Sign S_, Bits B_, i64 P_>
constexpr auto
lower_bound(Fixed<S_, B_, P_> val)
{
  return round_down<B>(val);
}

// utility definitions for literal types
// clang-format off
template<Bits B, IsReprOrFloat auto V> constexpr auto round_down_v  = round_down  <B>(as_fixed_v<V>);
template<Bits B, IsReprOrFloat auto V> constexpr auto round_up_v    = round_up    <B>(as_fixed_v<V>);
template<Bits B, IsReprOrFloat auto V> constexpr auto upper_bound_v = upper_bound <B>(as_fixed_v<V>);
template<Bits B, IsReprOrFloat auto V> constexpr auto lower_bound_v = lower_bound <B>(as_fixed_v<V>);
// clang-format on
