#pragma once

#include "../ieee754.hpp"
#include "../repr.hpp"

#include <type_traits>

namespace internal {

template<Bits B_, i64 P_>
constexpr auto
conversion_as_fixed_helper_repr_(IsRepr auto val)
{
  if constexpr (std::is_signed_v<decltype(val)>)
    return Fixed<VAR, B_, P_>::from_repr(rshift(val, P_));
  else
    return Fixed<POS, B_, P_>::from_repr(rshift(val, P_));
}

template<Bits B_, i64 P_>
constexpr auto
conversion_as_fixed_helper_float_(f32 ieee754)
{
  const auto [significant, power] = ieee754::decompose<f32>(ieee754);
  return Fixed<VAR, B_, P_>::from_repr(lshift(significant, power - P_));
}

template<Bits B_, i64 P_>
constexpr auto
conversion_as_fixed_helper_double_(f64 ieee754)
{
  const auto [significant, power] = ieee754::decompose<f64>(ieee754);
  return Fixed<VAR, B_, P_>::from_repr(lshift(significant, power - P_));
}

}

template<Bits B_, i64 P_>
constexpr auto
as_fixed(IsReprOrFloat auto val)
{
  if constexpr (IsRepr<decltype(val)>)
    return internal::conversion_as_fixed_helper_repr_<B_, P_>(val);

  if constexpr (std::is_same_v<decltype(val), f32>)
    return internal::conversion_as_fixed_helper_float_<B_, P_>(val);

  if constexpr (std::is_same_v<decltype(val), f64>)
    return internal::conversion_as_fixed_helper_double_<B_, P_>(val);
}
