#pragma once

#include "./bits.hpp"

#include <limits>

namespace numeric::ieee754 {

namespace internal {

constexpr auto
sign_float_helper_(float ieee754)
{
  static_assert(std::numeric_limits<float>::is_iec559);
  return static_cast<u8>(std::bit_cast<u32>(ieee754) >> 31);
}

constexpr auto
sign_double_helper_(double ieee754)
{
  static_assert(std::numeric_limits<double>::is_iec559);
  return static_cast<u8>(std::bit_cast<u64>(ieee754) >> 63);
}

constexpr i8
power_float_helper_(float ieee754)
{
  static_assert(std::numeric_limits<float>::is_iec559);

  if (ieee754 == 0.0f)
    return 0;

  const auto raw = std::bit_cast<u32>(ieee754);
  const auto exponent = (raw & 0x7F80'0000) >> 23;

  if (exponent == 0)
    return static_cast<i8>(-149);

  return static_cast<i8>(static_cast<i32>(exponent) - 150);
}

constexpr i16
power_double_helper_(double ieee754)
{
  static_assert(std::numeric_limits<double>::is_iec559);

  if (ieee754 == 0.0)
    return 0;

  const auto raw = std::bit_cast<u64>(ieee754);
  const auto exponent = (raw & 0x7FF0'0000'0000'0000) >> 52;

  if (exponent == 0)
    return -1074;

  return static_cast<i16>(static_cast<i32>(exponent) - 1075);
}

constexpr u32
abs_significant_float_helper_(float ieee754)
{
  static_assert(std::numeric_limits<float>::is_iec559);

  if (ieee754 == 0.0f)
    return 0;

  const auto raw = std::bit_cast<u32>(ieee754);
  const auto exponent = (raw & 0x7F80'0000) >> 23;
  const auto mantissa = raw & 0x007F'FFFF;

  if (exponent == 0)
    return mantissa;

  return set_bits<24>(mantissa);
}

constexpr u64
abs_significant_double_helper_(double ieee754)
{
  static_assert(std::numeric_limits<double>::is_iec559);

  if (ieee754 == 0.0)
    return 0;

  const auto raw = std::bit_cast<u64>(ieee754);
  const auto exponent = (raw & 0x7FF0'0000'0000'0000) >> 52;
  const auto mantissa = raw & 0x000F'FFFF'FFFF'FFFF;

  if (exponent == 0)
    return mantissa;

  return set_bits<53>(mantissa);
}

}

constexpr auto
sign(IsFloat auto ieee754)
{
  if constexpr (std::is_same_v<float, decltype(ieee754)>)
    return internal::sign_float_helper_(ieee754);

  if constexpr (std::is_same_v<double, decltype(ieee754)>)
    return internal::sign_double_helper_(ieee754);
}

constexpr auto
power(IsFloat auto ieee754)
{
  if constexpr (std::is_same_v<float, decltype(ieee754)>)
    return internal::power_float_helper_(ieee754);

  if constexpr (std::is_same_v<double, decltype(ieee754)>)
    return internal::power_double_helper_(ieee754);
}

constexpr auto
abs_significant(IsFloat auto ieee754)
{
  if constexpr (std::is_same_v<float, decltype(ieee754)>)
    return internal::abs_significant_float_helper_(ieee754);

  if constexpr (std::is_same_v<double, decltype(ieee754)>)
    return internal::abs_significant_double_helper_(ieee754);
}

constexpr auto
significant(IsFloat auto ieee754)
{
  const auto s = abs_significant(ieee754);
  return sign(ieee754) ? -s : s;
}

// clang-format off
template<IsFloat auto V> constexpr auto sign_v            = sign(V);
template<IsFloat auto V> constexpr auto power_v           = power(V);
template<IsFloat auto V> constexpr auto significant_v     = significant(V);
template<IsFloat auto V> constexpr auto abs_significant_v = abs_significant(V);
// clang-format on

/// combines significant and power retrival for rt queries.
/// notice: not useful for ct, as member access is not constexpr.
template<typename>
struct decompose;

template<>
struct decompose<float>
{
  i32 significant;
  i8 power;

  constexpr explicit decompose(float ieee754)
  {
    static_assert(std::numeric_limits<float>::is_iec559);

    if (ieee754 == 0.0f) {
      significant = 0;
      power = 0;
    } else {

      const auto raw = std::bit_cast<u32>(ieee754);
      const auto exponent = (raw & 0x7F80'0000) >> 23;
      const auto mantissa = static_cast<i32>(raw & 0x007F'FFFF);
      const auto sign = std::bit_cast<u32>(ieee754) >> 31;

      if (exponent == 0) {
        significant = sign ? -mantissa : mantissa;
        power = static_cast<i8>(-149);
      } else {
        const auto mantissa_ = set_bits<24>(mantissa);
        significant = sign ? -mantissa_ : mantissa_;
        power = static_cast<i8>(static_cast<i32>(exponent) - 150);
      }
    }
  }
};

template<>
struct decompose<double>
{
  i64 significant;
  i16 power;

  constexpr explicit decompose(double ieee754)
  {
    static_assert(std::numeric_limits<double>::is_iec559);

    if (ieee754 == 0.0) {
      significant = 0;
      power = 0;
    } else {

      const auto raw = std::bit_cast<u64>(ieee754);
      const auto exponent = (raw & 0x7FF0'0000'0000'0000) >> 52;
      const auto mantissa = static_cast<i64>(raw & 0x000F'FFFF'FFFF'FFFF);
      const auto sign = std::bit_cast<u64>(ieee754) >> 63;

      if (exponent == 0) {
        significant = sign ? -mantissa : mantissa;
        power = static_cast<i16>(-1074);
      } else {
        const auto mantissa_ = set_bits<53>(mantissa);
        significant = sign ? -mantissa_ : mantissa_;
        power = static_cast<i16>(static_cast<i32>(exponent) - 1075);
      }
    }
  }
};

}
