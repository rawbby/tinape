#pragma once

#include "./base.hpp"
#include "./bits.hpp"
#include "./sign.hpp"

#include <type_traits>
#include <assert.hpp>

namespace internal {
template<Sign S, Bits B>
static constexpr auto
repr_helper_()
{
  // clang-format off
  static_assert(B+(S==VAR)<=0x40, "no int can represent this amount of bits");
  if constexpr (S==VAR) {
         if constexpr(B>0x1F) return i64{};
    else if constexpr(B>0x0F) return i32{};
    else if constexpr(B>0x07) return i16{};
    else                      return i8{};
  } else {
         if constexpr(B>0x20) return u64{};
    else if constexpr(B>0x10) return u32{};
    else if constexpr(B>0x08) return u16{};
    else                      return u8{};
  }
  // clang-format on
}
}

/// Helper class for compile-time numeric type representation.
/// Provides logic to select the minimal built-in integer type
/// capable of holding a specified number of bits and sign indicator.
template<Sign S, Bits B>
using Repr = decltype(internal::repr_helper_<S, B>());

constexpr auto
lshift(IsRepr auto repr, i64 shift)
{
  using urepr = Repr<POS, sizeof(repr) << 3>;

  if constexpr (std::is_signed_v<decltype(repr)>) {

    if (repr < 0)
      return static_cast<decltype(repr)>(-lshift(static_cast<urepr>(-repr), shift));
    return static_cast<decltype(repr)>(lshift(static_cast<urepr>(repr), shift));

  } else {

    if (shift < 0)
      return static_cast<decltype(repr)>(repr >> static_cast<Bits>(-shift));
    return static_cast<decltype(repr)>(repr << static_cast<Bits>(shift));
  }
}

constexpr auto
rshift(IsRepr auto repr, i64 shift)
{
  if (shift < 0)
    return repr << static_cast<Bits>(-shift);
  return repr >> static_cast<Bits>(shift);
}

template<Sign S, Bits B>
constexpr auto
repr_cast(IsRepr auto repr)
{
  constexpr auto B_ = (sizeof(repr) << 3) - std::is_signed_v<decltype(repr)>;

  if (S == NIL)
    DASSERT_EQ(repr, 0);
  else if (S != VAR)
    DASSERT_GE(repr, 0);

  if (B < B_)
    DASSERT_EQ((mask<B_, B>(repr < 0 ? -repr : repr)), 0);

  return static_cast<Repr<S, B>>(repr);
}
