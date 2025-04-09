#pragma once

#include "./repr.hpp"

// clang-format off
namespace internal{enum class IsIntHelper_{};}
// clang-format on

template<typename T>
concept IsInt = std::is_same_v<typename T::TypeId, internal::IsIntHelper_>;

/// Numerically stable integer type with custom sign and bit-width.
/// It provides basic arithmetic operations with compile-time
/// resolution of a big enough underlying representation.
///
/// @tparam S_ Sign indicator (NIL, POS, NEG, VAR).
/// @tparam B_ Bit-width of the integer (without sign bit).
template<Sign S_, Bits B_>
struct Int
{
  using TypeId = internal::IsIntHelper_;

private:
  static_assert(S_ != NIL || !B_, "nil sign implies zero bits");
  static_assert(B_ || S_ == NIL, "zero bits implies nil sign");

public:
  using Repr_ = Repr<S_, B_>;
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

  static constexpr Int max()
  {
    Int tmp;
    tmp.repr_ = (1 << bits_) - 1;
    return tmp;
  }

  static constexpr Int min()
  {
    Int tmp;
    tmp.repr_ = 1;
    return tmp;
  }
};
