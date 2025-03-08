#pragma once

#include "../ieee754.hpp"
#include "../repr.hpp"

#include <type_traits>

namespace numeric {

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
conversion_as_fixed_helper_float_(float ieee754)
{
  const auto [significant, power] = ieee754::decompose<float>(ieee754);
  return Fixed<VAR, B_, P_>::from_repr(lshift(significant, power - P_));
}

template<Bits B_, i64 P_>
constexpr auto
conversion_as_fixed_helper_double_(double ieee754)
{
  const auto [significant, power] = ieee754::decompose<double>(ieee754);
  return Fixed<VAR, B_, P_>::from_repr(lshift(significant, power - P_));
}

}

template<Bits B_, i64 P_>
constexpr auto
as_fixed(IsReprOrFloat auto val)
{
  if constexpr (IsRepr<decltype(val)>)
    return internal::conversion_as_fixed_helper_repr_<B_, P_>(val);

  if constexpr (std::is_same_v<decltype(val), float>)
    return internal::conversion_as_fixed_helper_float_<B_, P_>(val);

  if constexpr (std::is_same_v<decltype(val), double>)
    return internal::conversion_as_fixed_helper_double_<B_, P_>(val);
}

}
