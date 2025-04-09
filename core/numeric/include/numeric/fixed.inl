#pragma once

template<Sign S, Bits B, i64 P>
constexpr Fixed<S, B, P>::Fixed()
  : repr()
{
}

template<Sign S, Bits B, i64 P>
constexpr Fixed<S, B, P>::Fixed(IsFixed auto rhs)
  : repr(repr_cast<S, B>(lshift(rhs.repr, FixedTraits<decltype(rhs)>::P - P)))
{
}

template<Sign S, Bits B, i64 P>
constexpr Fixed<S, B, P>::Fixed(IsRepr auto rhs)
  : repr(repr_cast<S, B>(rshift(rhs, P)))
{
}

template<Sign S, Bits B, i64 P>
constexpr Fixed<S, B, P>::Fixed(IsFloat auto ieee754)
{
  const auto [s, p] = ieee754::decompose<decltype(ieee754)>(ieee754);
  repr = repr_cast<S, B>(lshift(s, p - P));
}

template<Sign S, Bits B, i64 P>
constexpr Fixed<S, B, P>
Fixed<S, B, P>::from_repr(IsRepr auto repr)
{
  auto result = Fixed{};
  result.repr = repr_cast<S, B>(repr);
  return result;
}

template<Sign S, Bits B, i64 P>
constexpr Fixed<S, B, P>
Fixed<S, B, P>::max()
{
  Fixed tmp;
  tmp.repr = (1 << B) - 1;
  return tmp;
}

template<Sign S, Bits B, i64 P>
constexpr Fixed<S, B, P>
Fixed<S, B, P>::min()
{
  Fixed tmp;
  tmp.repr = 1;
  return tmp;
}
