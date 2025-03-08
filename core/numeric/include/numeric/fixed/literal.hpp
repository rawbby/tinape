#pragma once

#include "../fixed.hpp"
#include "../ieee754.hpp"

#include <bit>
#include <iostream>

namespace numeric {

namespace internal {

template<double IEEE754>
constexpr auto
literal_as_fixed_helper_double_()
{
  constexpr auto I = ieee754::abs_significant_v<IEEE754>;
  constexpr auto O = count_right_zeros(I);
  constexpr auto R = I >> O;

  constexpr auto S = ieee754::sign_v<IEEE754> ? NEG : POS;
  constexpr auto B = std::bit_width(R);
  constexpr auto P = ieee754::power_v<IEEE754> + O;

  return Fixed<S, B, P>::from_repr(R);
}

template<IsRepr auto I>
constexpr auto
as_fixed_helper_int_()
{
  constexpr auto O = count_right_zeros(I);
  constexpr auto R = I >> O;
  return Fixed<POS, std::bit_width(R), O>{ R };
}

template<IsReprOrFloat auto V>
constexpr auto
as_fixed_helper_()
{
  if constexpr (IsRepr<decltype(V)>)
    return as_fixed_helper_int_<V>();

  if constexpr (std::is_same_v<float, decltype(V)>)
    return literal_as_fixed_helper_double_<static_cast<double>(V)>();

  if constexpr (std::is_same_v<double, decltype(V)>)
    return literal_as_fixed_helper_double_<V>();
}

}

template<IsReprOrFloat auto I>
constexpr auto as_fixed_v = internal::as_fixed_helper_<I>();

}
