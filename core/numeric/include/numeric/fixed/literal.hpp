#pragma once

#include "../fixed.hpp"

#include <bit>

namespace numeric {

namespace internal {

template<double D>
constexpr auto
as_fixed_helper_double_()
{
  constexpr auto raw = std::bit_cast<u64>(D);
  constexpr auto bias_exp = static_cast<i32>(mask_shift<63, 52>(raw));
  constexpr auto exponent = bias_exp ? (bias_exp - 1023) : -1022;
  constexpr auto fraction = mask<52, 0>(raw);
  constexpr auto mantissa = bias_exp ? set_bits<53>(fraction) : fraction;

  static_assert(std::numeric_limits<double>::is_iec559);
  static_assert(bias_exp != 0x7FF); // nan and inf unsupported

  if constexpr (raw == 0)
    return Fixed<NIL, 0, 0>{};

  else {
    constexpr auto S = mask<64>(raw) ? NEG : POS;
    constexpr auto O = count_right_zeros(mantissa);
    constexpr auto P = exponent - 52 + O;
    constexpr auto B = std::bit_width(mantissa >> O);
    return Fixed<S, B, P>{ D < 0 ? -D : D };
  }
}

template<IsRepr auto I>
constexpr auto
as_fixed_helper_int_()
{
  constexpr auto O = count_right_zeros(I);
  constexpr auto R = I >> O;
  return Fixed<POS, std::bit_width(R), O>{ R };
}

template<auto V>
constexpr auto
as_fixed_helper_()
{
  if constexpr (IsRepr<decltype(V)>)
    return as_fixed_helper_int_<V>();
  else
    return as_fixed_helper_double_<static_cast<double>(V)>();
}

}

template<auto I>
constexpr auto as_fixed = internal::as_fixed_helper_<I>();

}
