#pragma once

#include "bits.hpp"

template<Bits B>
constexpr auto
round_down(IsFixed auto val)
{
  using Val = FixedTraits<decltype(val)>;
  return Fixed<Val::S, B, Val::P + Val::B - B>{ val };
}

template<Bits B>
constexpr auto
round_up(IsFixed auto val)
{
  using Val = FixedTraits<decltype(val)>;
  auto res = Fixed<Val::S, B, Val::P + Val::B - B>{ val };
  if (B < Val::B)
    res.repr += mask<Val::B - B>(val.repr) != 0;
  return res;
}

template<Bits B>
constexpr auto
upper_bound(IsFixed auto val)
{
  using Val = FixedTraits<decltype(val)>;
  auto res = Fixed<Val::S, B, Val::P + Val::B - B>{ val };
  res.repr += 1;
  return res;
}

template<Bits B>
constexpr auto
lower_bound(IsFixed auto val)
{
  return round_down<B>(val);
}
