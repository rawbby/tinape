#pragma once

#include "./repr.hpp"

#include <algorithm>
#include <limits>
#include <bit>

namespace numeric {

/// Numerically stable fixed-point type with custom sign, bit-width and scaling.
/// It supports conversion from IEEE 754 floating-point types and provides
/// basic arithmetic operations with compile-time resolution of a big enough
/// underlying representation.
///
/// @tparam S_ Sign indicator (NIL, POS, NEG, VAR).
/// @tparam B_ Bit-width of the integer (without sign bit).
/// @tparam P_ Fixed-point scaling power.
template<Sign S_, Bits B_, i64 P_>
struct Fixed
{
private:
  static_assert(S_ != NIL || !P_, "nil sign implies zero power");
  static_assert(S_ != NIL || !B_, "nil sign implies zero bits");
  static_assert(B_ || S_ == NIL, "zero bits implies nil sign");
  using Repr_ = Repr<S_, B_>;

public:
  static constexpr auto sign_ = S_;
  static constexpr auto bits_ = B_;
  static constexpr auto power_ = P_;
  Repr_ repr_;

  template<Sign S, Bits B, i64 P>
  constexpr Fixed(const Fixed<S, B, P>& rhs)
    : repr_(repr_cast<S_, B_>(lshift(rhs.repr_, P - P_)))
  {
  }

  constexpr Fixed()
    : repr_()
  {
  }

  constexpr Fixed(double ieee754)
  {
    static_assert(std::numeric_limits<double>::is_iec559);
    const auto raw = std::bit_cast<u64>(ieee754);

    const auto bias_exp = static_cast<i32>(mask_shift<63, 52>(raw));
    const auto exponent = bias_exp ? (bias_exp - 1023) : -1022;
    DEBUG_ASSERT_NE(bias_exp, 0x7FF, "nan and inf unsupported");

    const auto fraction = mask<52, 0>(raw);
    const auto mantissa = bias_exp ? set_bits<53>(fraction) : fraction;
    repr_ = lshift(mantissa, exponent - 52 - P_);

    if (S_ == VAR && mask<64>(raw))
      repr_ = -repr_;

    repr_ = repr_cast<S_, B_>(repr_);
  }

  constexpr Fixed(float ieee754)
  {
    static_assert(std::numeric_limits<float>::is_iec559);
    const auto raw = std::bit_cast<u32>(ieee754);

    const auto bias_exp = static_cast<i32>(mask_shift<31, 23>(raw));
    const auto exponent = bias_exp ? (bias_exp - 127) : -126;
    DEBUG_ASSERT_NE(bias_exp, 0xFF, "nan and inf unsupported");

    const auto fraction = mask<23, 0>(raw);
    const auto mantissa = bias_exp ? set_bits<24>(fraction) : fraction;
    repr_ = lshift(mantissa, exponent - 23 - P_);

    if (S_ == VAR && mask<32>(raw))
      repr_ = -repr_;

    repr_ = repr_cast<S_, B_>(repr_);
  }

  static constexpr Fixed from_repr(IsRepr auto repr)
  {
    auto result = Fixed{};
    result.repr_ = repr_cast<S_, B_>(repr);
    return result;
  }
};

}
