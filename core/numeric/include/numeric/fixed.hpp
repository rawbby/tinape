#pragma once

#include "./ieee754.hpp"
#include "./repr.hpp"

// clang-format off
namespace internal{enum class IsFixedHelper_{};}
// clang-format on

template<typename T>
concept IsFixed = std::is_same_v<typename T::TypeId, internal::IsFixedHelper_>;

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
  using TypeId = internal::IsFixedHelper_;

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

  constexpr Fixed(IsFloat auto ieee754)
  {
    const auto [s, p] = ieee754::decompose<decltype(ieee754)>(ieee754);
    repr_ = repr_cast<S_, B_>(lshift(s, p - P_));
  }

  static constexpr Fixed from_repr(IsRepr auto repr)
  {
    auto result = Fixed{};
    result.repr_ = repr_cast<S_, B_>(repr);
    return result;
  }

  static constexpr Fixed max()
  {
    Fixed tmp;
    tmp.repr_ = (1 << bits_) - 1;
    return tmp;
  }

  static constexpr Fixed min()
  {
    Fixed tmp;
    tmp.repr_ = 1;
    return tmp;
  }
};
