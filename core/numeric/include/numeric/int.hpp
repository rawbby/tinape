#pragma once

#include "./repr.hpp"

namespace numeric {

/// Numerically stable integer type with custom sign and bit-width.
/// It provides basic arithmetic operations with compile-time
/// resolution of a big enough underlying representation.
///
/// @tparam S_ Sign indicator (NIL, POS, NEG, VAR).
/// @tparam B_ Bit-width of the integer (without sign bit).
template<Sign S_, Bits B_>
struct Int
{
private:
  static_assert(S_ != NIL || !B_, "nil sign implies zero bits");
  static_assert(B_ || S_ == NIL, "zero bits implies nil sign");
  using Repr_ = Repr<S_, B_>;

public:
  static constexpr auto sign_ = S_;
  static constexpr auto bits_ = B_;
  Repr_ repr_;

  template<Sign S, Bits B>
  constexpr Int(Int<S, B> rhs)
    : repr_(repr_cast<S_, B_>(rhs.repr_))
  {
  }

  constexpr Int(IsRepr auto repr)
    : repr_(repr_cast<S_, B_>(repr))
  {
  }

  constexpr Int()
    : repr_()
  {
  }
};

}
