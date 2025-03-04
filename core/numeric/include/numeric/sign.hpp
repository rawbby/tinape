#pragma once

#include "./base.hpp"

namespace numeric {

/// These constants serve as compile-time hints for numeric type signedness.
enum class Sign : u8
{
  NIL = 0b00, ///< Zero value; no bits stored.
  POS = 0b01, ///< Unsigned type.
  NEG = 0b10, ///< Negative value with implicit sign.
  VAR = 0b11  ///< Signed type with explicit sign.
};

using enum Sign;

// clang-format off

constexpr Sign
operator-(Sign s)
{
  if (s == POS) return NEG;
  if (s == NEG) return POS;
  return s;
}

constexpr Sign
operator+(Sign s_, Sign s)
{
  if (s_ == s)   return s_;
  if (s_ == NIL) return s;
  if (s == NIL)  return s_;
  return VAR;
}

constexpr Sign
operator*(Sign s_, Sign s)
{
  if (s_ == NIL || s == NIL) return NIL;
  if (s_ == VAR || s == VAR) return VAR;
  if (s_ == s) return POS;
  return NEG;
}

constexpr Sign operator-(Sign s_,Sign s){return s_+(-s);}
constexpr Sign operator/(Sign s_,Sign s){return s_*s;}

// clang-format on

}
