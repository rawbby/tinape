#pragma once

#include "../fixed.hpp"

namespace numeric {

template<Sign S_, Bits B_, i64 P_>
constexpr auto
operator-(Fixed<S_, B_, P_> lhs)
{
  if (S_ == VAR)
    return Fixed<-S_, B_, P_>::from_repr(-lhs.repr_);
  return Fixed<-S_, B_, P_>::from_repr(lhs.repr_);
}

template<Sign S_, Bits B_, i64 P_, Sign S, Bits B, i64 P>
constexpr auto
operator+(Fixed<S_, B_, P_> lhs, Fixed<S, B, P> rhs)
{
  if constexpr (S_ == NIL)
    return rhs;

  else if constexpr (S == NIL)
    return lhs;

  else {
    constexpr auto P__ = std::min(P_, P);
    constexpr auto SFT_ = P_ - P__;
    constexpr auto SFT = P - P__;
    constexpr auto B__ = std::max(B_ + SFT_, B + SFT) + 1;
    constexpr auto S__ = S_ + S;

    const auto res_ = static_cast<Repr<S__, B__>>(lhs.repr_) << SFT_;
    res_ += static_cast<Repr<S__, B__>>(rhs.repr_) << SFT;

    return Fixed<S__, B__, P__>::from_repr(res_);
  }
}

template<Sign S_, Bits B_, i64 P_, Sign S, Bits B, i64 P>
constexpr auto
operator-(Fixed<S_, B_, P_> lhs, Fixed<S, B, P> rhs)
{
  return lhs + (-rhs);
}

template<Sign S_, Bits B_, i64 P_, Sign S, Bits B, i64 P>
constexpr auto
operator*(Fixed<S_, B_, P_> lhs, Fixed<S, B, P> rhs)
{
  constexpr Sign S__ = S_ * S;
  constexpr Bits B__ = [=] {
    // clang-format off
    if (B_ == 1) return B;
    if (B == 1) return B_;
    return static_cast<Bits> (B_ + B);
    // clang-format on
  }();

  if constexpr (S__ == NIL)
    return Fixed<NIL, 0, 0>{};

  else {
    constexpr auto P__ = P_ + P;

    auto res_ = static_cast<Repr<S__, B__>>(lhs.repr_);
    res_ *= rhs.repr_;

    return Fixed<S__, B__, P__>::from_repr(res_);
  }
}

}
