#pragma once

#include <cnl/elastic_integer.h>
#include <cnl/fixed_point.h>

template<typename T>
constexpr inline int
GetFloatBits()
{
  return cnl::_impl::width<cnl::_impl::rep_t<T>>::value;
}
