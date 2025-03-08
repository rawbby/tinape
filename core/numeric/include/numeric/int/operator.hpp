#pragma once

#include "../int.hpp"
#include "../repr.hpp"

#include <assert.hpp>

namespace numeric {

template<Sign S_, Bits B_>
constexpr auto
operator-(Int<S_, B_> lhs)
{
  if (S_ == VAR)
    return Int<-S_, B_>{ -lhs.repr_ };
  return Int<-S_, B_>{ lhs.repr_ };
}

template<Sign S_, Bits B_, Sign S, Bits B>
constexpr auto
operator+(Int<S_, B_> lhs, Int<S, B> rhs)
{
  if constexpr (S_ == NIL)
    return rhs;

  else if constexpr (S == NIL)
    return lhs;

  else {
    constexpr Sign S__ = S_ + S;
    constexpr Bits B__ = std::max(B_, B) + 1;

    auto repr = static_cast<Repr<S__, B__>>(lhs.repr_);
    repr += rhs.repr_;

    return Int<S__, B__>{ repr };
  }
}

template<Sign S_, Bits B_, Sign S, Bits B>
constexpr auto
operator-(Int<S_, B_> lhs, Int<S, B> rhs)
{
  return lhs + (-rhs);
}

template<Sign S_, Bits B_, Sign S, Bits B>
constexpr auto
operator*(Int<S_, B_> lhs, Int<S, B> rhs)
{
  constexpr Sign S__ = S_ * S;

  if constexpr (S__ == NIL)
    return Int<NIL, 0>{};

  else {
    constexpr Bits B__ = B_ + B;

    auto repr = static_cast<Repr<S__, B__>>(lhs.repr_);
    repr *= rhs.repr_;

    return Int<S__, B__>{ repr };
  }
}

template<Sign S_, Bits B_, Sign S, Bits B>
constexpr auto
operator/(Int<S_, B_> lhs, Int<S, B> rhs)
{
  static_assert(S != NIL, "division by zero");
  //DEBUG_ASSERT_NE(rhs.repr_, 0, "division by zero");

  if constexpr (S_ == NIL)
    return Int<NIL, 0U>{};

  else {
    constexpr Sign S__ = S_ / S;
    constexpr Bits B__ = B_;

    auto repr = static_cast<Repr<S__, B__>>(lhs.repr_);
    repr /= rhs.repr_;

    return Int<S__, B__>{ repr };
  }
}

}
