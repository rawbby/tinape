#pragma once

#include "./ieee754.hpp"
#include "./repr.hpp"

#include <numbers>

// clang-format off
namespace internal{enum class IsFixedHelper_{};}
// clang-format on

template<typename Fixed>
concept IsFixed = std::is_same_v<typename Fixed::TypeId, internal::IsFixedHelper_>;

template<typename Fixed>
struct FixedTraits
{
  using Repr = typename Fixed::Repr;
  static constexpr Sign S = Fixed::S;
  static constexpr Bits B = Fixed::B;
  static constexpr i64 P = Fixed::P;
};

/// Numerically stable fixed-point type with custom sign, bit-width and scaling.
/// It supports conversion from IEEE 754 floating-point types and provides
/// basic arithmetic operations with compile-time resolution of a big enough
/// underlying representation.
///
/// @tparam ArgS Sign indicator (NIL, POS, NEG, VAR).
/// @tparam ArgB Bit-width of the integer (without sign bit).
/// @tparam ArgP Fixed-point scaling power.
template<Sign ArgS, Bits ArgB, i64 ArgP>
struct Fixed
{
  static constexpr auto S = ArgS;
  static constexpr auto B = ArgB;
  static constexpr auto P = ArgP;

  using TypeId = internal::IsFixedHelper_;
  static_assert(S != NIL || !P, "nil sign implies zero power");
  static_assert(S != NIL || !B, "nil sign implies zero bits");
  static_assert(B || S == NIL, "zero bits implies nil sign");

  using Repr = Repr<S, B>;
  Repr repr;

  constexpr Fixed();
  constexpr Fixed(IsFixed auto);
  constexpr Fixed(IsRepr auto);
  constexpr Fixed(IsFloat auto);

  static constexpr Fixed from_repr(IsRepr auto);

  static constexpr Fixed max();
  static constexpr Fixed min();
};

#include "fixed.inl"

// clang-format off
template<IsReprOrFloat auto T> constexpr auto as_fixed();
template<IsReprOrFloat auto T> constexpr auto as_fixed_v = as_fixed<T>();
#include "fixed_literal.inl"
// clang-format on

// clang-format off
template<Bits B> constexpr auto round_down  (IsFixed auto);
template<Bits B> constexpr auto round_up    (IsFixed auto);
template<Bits B> constexpr auto upper_bound (IsFixed auto);
template<Bits B> constexpr auto lower_bound (IsFixed auto);
template<Bits B, IsReprOrFloat auto T> constexpr auto round_down_v  = round_down  <B>(as_fixed_v<T>);
template<Bits B, IsReprOrFloat auto T> constexpr auto round_up_v    = round_up    <B>(as_fixed_v<T>);
template<Bits B, IsReprOrFloat auto T> constexpr auto upper_bound_v = upper_bound <B>(as_fixed_v<T>);
template<Bits B, IsReprOrFloat auto T> constexpr auto lower_bound_v = lower_bound <B>(as_fixed_v<T>);
#include "fixed_round.inl"
// clang-format on

// clang-format off
constexpr auto fixed_zero                           = as_fixed_v<0u>;
constexpr auto fixed_one                            = as_fixed_v<1u>;
template<Bits B> constexpr auto fixed_e             = round_down_v  <B, std::numbers::e_v          <f64>>;
template<Bits B> constexpr auto fixed_log2e         = round_down_v  <B, std::numbers::log2e_v      <f64>>;
template<Bits B> constexpr auto fixed_log10e        = round_down_v  <B, std::numbers::log10e_v     <f64>>;
template<Bits B> constexpr auto fixed_pi            = round_down_v  <B, std::numbers::pi_v         <f64>>;
template<Bits B> constexpr auto fixed_inv_pi        = round_down_v  <B, std::numbers::inv_pi_v     <f64>>;
template<Bits B> constexpr auto fixed_inv_sqrtpi    = round_down_v  <B, std::numbers::inv_sqrtpi_v <f64>>;
template<Bits B> constexpr auto fixed_ln2           = round_down_v  <B, std::numbers::ln2_v        <f64>>;
template<Bits B> constexpr auto fixed_ln10          = round_down_v  <B, std::numbers::ln10_v       <f64>>;
template<Bits B> constexpr auto fixed_sqrt2         = round_down_v  <B, std::numbers::sqrt2_v      <f64>>;
template<Bits B> constexpr auto fixed_sqrt3         = round_down_v  <B, std::numbers::sqrt3_v      <f64>>;
template<Bits B> constexpr auto fixed_inv_sqrt3     = round_down_v  <B, std::numbers::inv_sqrt3_v  <f64>>;
template<Bits B> constexpr auto fixed_egamma        = round_down_v  <B, std::numbers::egamma_v     <f64>>;
template<Bits B> constexpr auto fixed_phi           = round_down_v  <B, std::numbers::phi_v        <f64>>;
template<Bits B> constexpr auto fixed_e_ub          = upper_bound_v <B, std::numbers::e_v          <f64>>;
template<Bits B> constexpr auto fixed_log2e_ub      = upper_bound_v <B, std::numbers::log2e_v      <f64>>;
template<Bits B> constexpr auto fixed_log10e_ub     = upper_bound_v <B, std::numbers::log10e_v     <f64>>;
template<Bits B> constexpr auto fixed_pi_ub         = upper_bound_v <B, std::numbers::pi_v         <f64>>;
template<Bits B> constexpr auto fixed_inv_pi_ub     = upper_bound_v <B, std::numbers::inv_pi_v     <f64>>;
template<Bits B> constexpr auto fixed_inv_sqrtpi_ub = upper_bound_v <B, std::numbers::inv_sqrtpi_v <f64>>;
template<Bits B> constexpr auto fixed_ln2_ub        = upper_bound_v <B, std::numbers::ln2_v        <f64>>;
template<Bits B> constexpr auto fixed_ln10_ub       = upper_bound_v <B, std::numbers::ln10_v       <f64>>;
template<Bits B> constexpr auto fixed_sqrt2_ub      = upper_bound_v <B, std::numbers::sqrt2_v      <f64>>;
template<Bits B> constexpr auto fixed_sqrt3_ub      = upper_bound_v <B, std::numbers::sqrt3_v      <f64>>;
template<Bits B> constexpr auto fixed_inv_sqrt3_ub  = upper_bound_v <B, std::numbers::inv_sqrt3_v  <f64>>;
template<Bits B> constexpr auto fixed_egamma_ub     = upper_bound_v <B, std::numbers::egamma_v     <f64>>;
template<Bits B> constexpr auto fixed_phi_ub        = upper_bound_v <B, std::numbers::phi_v        <f64>>;
// clang-format on

// clang-format off
constexpr auto operator-(IsFixed auto);
constexpr auto operator+(IsFixed auto, IsFixed auto);
constexpr auto operator-(IsFixed auto, IsFixed auto);
constexpr auto operator*(IsFixed auto, IsFixed auto);
#include "fixed_arithmetic.inl"
// clang-format on

// clang-format off
constexpr bool operator==(IsFixed auto, IsFixed auto);
constexpr bool operator< (IsFixed auto, IsFixed auto);
constexpr bool operator!=(IsFixed auto lhs, IsFixed auto rhs) { return !(lhs == rhs); }
constexpr bool operator> (IsFixed auto lhs, IsFixed auto rhs) { return   rhs <  lhs ; }
constexpr bool operator<=(IsFixed auto lhs, IsFixed auto rhs) { return !(rhs <  lhs); }
constexpr bool operator>=(IsFixed auto lhs, IsFixed auto rhs) { return !(lhs <  rhs); }
#include "fixed_compare.inl"
// clang-format on

// clang-format off
//...
#include "fixed_convert.inl"
// clang-format on
