#pragma once

#include "ieee754.hpp"
#include "repr.hpp"

#include <type_traits>

namespace internal::fixed_convert {

template<Bits B, i64 P>
constexpr auto
repr_helper_(IsRepr auto val)
{
  if constexpr (std::is_signed_v<decltype(val)>)
    return Fixed<VAR, B, P>::from_repr(rshift(val, P));
  else
    return Fixed<POS, B, P>::from_repr(rshift(val, P));
}

template<Bits B, i64 P>
constexpr auto
float_helper_(IsFloat auto ieee754)
{
  const auto [significant, power] = ieee754::decompose<decltype(ieee754)>(ieee754);
  return Fixed<VAR, B, P>::from_repr(lshift(significant, power - P));
}

}

template<Bits B, i64 P>
constexpr auto
as_fixed(IsReprOrFloat auto val)
{
  if constexpr (IsRepr<decltype(val)>)
    return internal::fixed_convert::repr_helper_<B, P>(val);

  if constexpr (IsFloat<decltype(val)>)
    return internal::fixed_convert::float_helper_<B, P>(val);
}
