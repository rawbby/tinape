#pragma once

#include "../repr.hpp"

#include <type_traits>

constexpr auto
as_int(IsRepr auto repr)
{
  constexpr auto S = std::is_signed_v<decltype(repr)> ? VAR : POS;
  constexpr auto B = (sizeof(repr) << 3) - (S == VAR);
  return Int<S, B>{ repr };
}
