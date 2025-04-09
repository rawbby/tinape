#pragma once

#include "../int.hpp"

constexpr bool
operator==(IsInt auto lhs, IsInt auto rhs) noexcept
{
  return lhs.repr_ == rhs.repr_;
}

constexpr bool
operator!=(IsInt auto lhs, IsInt auto rhs) noexcept
{
  return lhs.repr_ != rhs.repr_;
}

constexpr bool
operator<(IsInt auto lhs, IsInt auto rhs) noexcept
{
  return lhs.repr_ < rhs.repr_;
}

constexpr bool
operator>(IsInt auto lhs, IsInt auto rhs) noexcept
{
  return lhs.repr_ > rhs.repr_;
}

constexpr bool
operator<=(IsInt auto lhs, IsInt auto rhs) noexcept
{
  return lhs.repr_ <= rhs.repr_;
}

constexpr bool
operator>=(IsInt auto lhs, IsInt auto rhs) noexcept
{
  return lhs.repr_ >= rhs.repr_;
}
