#pragma once

#include "ieee754.hpp"

#include <bit>

namespace internal::fixed_literal {

template<f64 IEEE754>
constexpr auto
double_helper_()
{
  if constexpr (IEEE754 == 0.0)
    return Fixed<NIL, 0, 0>{ 0.0f };

  else {
    constexpr auto I = ieee754::abs_significant_v<IEEE754>;
    constexpr auto O = count_right_zeros(I);
    constexpr auto R = I >> O;

    constexpr auto S = ieee754::sign_v<IEEE754> ? NEG : POS;
    constexpr auto B = std::bit_width(R);
    constexpr auto P = ieee754::power_v<IEEE754> + O;

    return Fixed<S, B, P>::from_repr(R);
  }
}

template<IsRepr auto I>
constexpr auto
int_helper_()
{
  if constexpr (I == 0)
    return Fixed<NIL, 0, 0>{ 0.0f };

  else {
    constexpr auto O = count_right_zeros(I);
    constexpr auto R = I >> O;
    return Fixed<POS, std::bit_width(R), O>{ R };
  }
}
}

template<IsReprOrFloat auto V>
constexpr auto
as_fixed()
{
  if constexpr (IsRepr<decltype(V)>)
    return internal::fixed_literal::int_helper_<V>();

  if constexpr (IsFloat<decltype(V)>)
    return internal::fixed_literal::double_helper_<static_cast<f64>(V)>();
}
