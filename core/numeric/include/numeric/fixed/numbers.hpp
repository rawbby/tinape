#pragma once

#include "../bits.hpp"
#include "./util.hpp"

#include <numbers>

namespace numeric::numbers {

// clang-format off
template<Bits B> constexpr auto e             = round_down_v  <B, std::numbers::e_v          <double>>;
template<Bits B> constexpr auto log2e         = round_down_v  <B, std::numbers::log2e_v      <double>>;
template<Bits B> constexpr auto log10e        = round_down_v  <B, std::numbers::log10e_v     <double>>;
template<Bits B> constexpr auto pi            = round_down_v  <B, std::numbers::pi_v         <double>>;
template<Bits B> constexpr auto inv_pi        = round_down_v  <B, std::numbers::inv_pi_v     <double>>;
template<Bits B> constexpr auto inv_sqrtpi    = round_down_v  <B, std::numbers::inv_sqrtpi_v <double>>;
template<Bits B> constexpr auto ln2           = round_down_v  <B, std::numbers::ln2_v        <double>>;
template<Bits B> constexpr auto ln10          = round_down_v  <B, std::numbers::ln10_v       <double>>;
template<Bits B> constexpr auto sqrt2         = round_down_v  <B, std::numbers::sqrt2_v      <double>>;
template<Bits B> constexpr auto sqrt3         = round_down_v  <B, std::numbers::sqrt3_v      <double>>;
template<Bits B> constexpr auto inv_sqrt3     = round_down_v  <B, std::numbers::inv_sqrt3_v  <double>>;
template<Bits B> constexpr auto egamma        = round_down_v  <B, std::numbers::egamma_v     <double>>;
template<Bits B> constexpr auto phi           = round_down_v  <B, std::numbers::phi_v        <double>>;
template<Bits B> constexpr auto e_ub          = upper_bound_v <B, std::numbers::e_v          <double>>;
template<Bits B> constexpr auto log2e_ub      = upper_bound_v <B, std::numbers::log2e_v      <double>>;
template<Bits B> constexpr auto log10e_ub     = upper_bound_v <B, std::numbers::log10e_v     <double>>;
template<Bits B> constexpr auto pi_ub         = upper_bound_v <B, std::numbers::pi_v         <double>>;
template<Bits B> constexpr auto inv_pi_ub     = upper_bound_v <B, std::numbers::inv_pi_v     <double>>;
template<Bits B> constexpr auto inv_sqrtpi_ub = upper_bound_v <B, std::numbers::inv_sqrtpi_v <double>>;
template<Bits B> constexpr auto ln2_ub        = upper_bound_v <B, std::numbers::ln2_v        <double>>;
template<Bits B> constexpr auto ln10_ub       = upper_bound_v <B, std::numbers::ln10_v       <double>>;
template<Bits B> constexpr auto sqrt2_ub      = upper_bound_v <B, std::numbers::sqrt2_v      <double>>;
template<Bits B> constexpr auto sqrt3_ub      = upper_bound_v <B, std::numbers::sqrt3_v      <double>>;
template<Bits B> constexpr auto inv_sqrt3_ub  = upper_bound_v <B, std::numbers::inv_sqrt3_v  <double>>;
template<Bits B> constexpr auto egamma_ub     = upper_bound_v <B, std::numbers::egamma_v     <double>>;
template<Bits B> constexpr auto phi_ub        = upper_bound_v <B, std::numbers::phi_v        <double>>;
// clang-format on

}
