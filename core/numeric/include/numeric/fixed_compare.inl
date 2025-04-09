#pragma once

constexpr bool
operator==(IsFixed auto lhs, IsFixed auto rhs)
{
  using Lhs = FixedTraits<decltype(lhs)>;
  using Rhs = FixedTraits<decltype(rhs)>;

  // handle first var by conversion
  if constexpr (Lhs::S == VAR) {
    if (lhs.repr < 0) {
      auto tmp = Fixed<NEG, Lhs::B, Lhs::P>{};
      tmp.repr = std::abs(lhs.repr);
      return tmp == rhs;
    }
    if (lhs.repr > 0) {
      auto tmp = Fixed<POS, Lhs::B, Lhs::P>{};
      tmp.repr = std::abs(lhs.repr);
      return tmp == rhs;
    }
    return fixed_zero == rhs;
  }

  // handle second var by conversion
  if constexpr (Rhs::S == VAR) {
    if (rhs.repr < 0) {
      auto tmp = Fixed<NEG, Rhs::B, Rhs::P>{};
      tmp.repr = std::abs(rhs.repr);
      return lhs == tmp;
    }
    if (rhs.repr > 0) {
      auto tmp = Fixed<POS, Rhs::B, Rhs::P>{};
      tmp.repr = std::abs(rhs.repr);
      return lhs == tmp;
    }
    return lhs == fixed_zero;
  }

  // handle nil
  else if constexpr (Lhs::S == NIL && Rhs::S == NIL)
    return true;
  else if constexpr (Lhs::S == NIL)
    return !rhs.repr;
  else if constexpr (Rhs::S == NIL)
    return !lhs.repr;

  // handle contrary signs
  else if constexpr (Lhs::S == POS && Rhs::S == NEG)
    return false;
  else if constexpr (Lhs::S == NEG && Rhs::S == POS)
    return false;

  // handle same signs -> underlying repr are both unsigned
  else if ((Lhs::S == POS && Rhs::S == POS) || (Lhs::S == NEG && Rhs::S == NEG)) {
    // TODO subtraction could lead to an unnecessary overflow
    return (rhs - lhs).repr == 0;
  }
}

constexpr bool
operator<(IsFixed auto lhs, IsFixed auto rhs)
{
  using Lhs = FixedTraits<decltype(lhs)>;
  using Rhs = FixedTraits<decltype(rhs)>;

  // handle first var by conversion
  if constexpr (Lhs::S == VAR) {
    if (lhs.repr < 0) {
      auto tmp = Fixed<NEG, Lhs::B, Lhs::P>{};
      tmp.repr = std::abs(lhs.repr);
      return tmp < rhs;
    }
    if (lhs.repr > 0) {
      auto tmp = Fixed<POS, Lhs::B, Lhs::P>{};
      tmp.repr = std::abs(lhs.repr);
      return tmp < rhs;
    }
    return (fixed_zero < rhs);
  }

  // handle second var by conversion
  else if constexpr (Rhs::S == VAR) {
    if (rhs.repr < 0) {
      auto tmp = Fixed<NEG, Rhs::B, Rhs::P>{};
      tmp.repr = std::abs(rhs.repr);
      return lhs < tmp;
    }
    if (rhs.repr > 0) {
      auto tmp = Fixed<POS, Rhs::B, Rhs::P>{};
      tmp.repr = std::abs(rhs.repr);
      return lhs < tmp;
    }
    return lhs < fixed_zero;
  }

  // handle nil
  if constexpr (Lhs::S == NIL && Rhs::S == NIL)
    return false;

  else if constexpr (Lhs::S == NIL && Rhs::S == NEG)
    return false;
  else if constexpr (Lhs::S == NIL && Rhs::S == POS)
    return rhs.repr;

  else if constexpr (Rhs::S == NIL && Lhs::S == NEG)
    return lhs.repr;
  else if constexpr (Rhs::S == NIL && Lhs::S == POS)
    return false;

  // handle contrary signs
  else if constexpr (Lhs::S == POS && Rhs::S == NEG)
    return false;
  else if constexpr (Lhs::S == NEG && Rhs::S == POS)
    return true;

  // handle same signs -> underlying repr are both unsigned
  else if ((Lhs::S == POS && Rhs::S == POS) || (Lhs::S == NEG && Rhs::S == NEG)) {
    // TODO subtraction could lead to an unnecessary overflow
    return (rhs - lhs).repr < 0;
  }
}
