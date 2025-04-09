#pragma once

constexpr auto
operator-(IsFixed auto lhs)
{
  using Lhs = FixedTraits<decltype(lhs)>;
  using Result = Fixed<-Lhs::S, Lhs::B, Lhs::P>;

  return Result::from_repr(Lhs::S == VAR ? -lhs.repr : lhs.repr);
}

constexpr auto
operator+(IsFixed auto lhs, IsFixed auto rhs)
{
  using Lhs = FixedTraits<decltype(lhs)>;
  using Rhs = FixedTraits<decltype(rhs)>;

  if constexpr (Lhs::S == NIL)
    return rhs;

  else if constexpr (Rhs::S == NIL)
    return lhs;

  else {
    constexpr auto P = std::min(Lhs::P, Rhs::P);
    constexpr auto SFT_ = Lhs::P - P;
    constexpr auto SFT = Rhs::P - P;
    constexpr auto B = std::max(Lhs::B + SFT_, Rhs::B + SFT) + 1;
    constexpr auto S = Lhs::S + Rhs::S;

    auto res_ = static_cast<Repr<S, B>>(lhs.repr) << SFT_;

    if constexpr ((Rhs::S == POS && Lhs::S == NEG) || (Rhs::S == NEG && Lhs::S == POS))
      res_ -= static_cast<Repr<S, B>>(rhs.repr) << SFT;
    else
      res_ += static_cast<Repr<S, B>>(rhs.repr) << SFT;

    return Fixed<S, B, P>::from_repr(res_);
  }
}

constexpr auto
operator-(IsFixed auto lhs, IsFixed auto rhs)
{
  return lhs + -rhs;
}

constexpr auto
operator*(IsFixed auto lhs, IsFixed auto rhs)
{
  using Lhs = FixedTraits<decltype(lhs)>;
  using Rhs = FixedTraits<decltype(rhs)>;

  constexpr Sign S = Lhs::S * Rhs::S;
  constexpr Bits B = [=] {
    // clang-format off
    if (Lhs::B == 1) return Rhs::B;
    if (Rhs::B == 1) return Lhs::B;
    return static_cast<Bits> (Lhs::B + Rhs::B);
    // clang-format on
  }();

  if constexpr (S == NIL)
    return fixed_zero;

  else {
    constexpr auto P = Lhs::P + Rhs::P;

    auto res = static_cast<Repr<S, B>>(lhs.repr);
    res *= rhs.repr;

    return Fixed<S, B, P>::from_repr(res);
  }
}
