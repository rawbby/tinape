#pragma once

#include "../int.hpp"

#include <bit>

namespace numeric {

namespace internal {
template<IsRepr auto I>
constexpr auto
as_int_helper_()
{
  if constexpr (std::is_signed_v<decltype(I)>)
    return -as_int_helper_<static_cast<u64>(-I)>();

  else
    return Int<POS, std::bit_width(I)>{ I };
}
}

template<IsRepr auto I>
constexpr auto as_int_v = internal::as_int_helper_<I>();

}
