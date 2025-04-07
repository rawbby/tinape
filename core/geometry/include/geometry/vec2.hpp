#pragma once

#include <type_traits>

// clang-format off
namespace internal{enum class IsVec2Helper_{};}
// clang-format on

template<typename T>
concept IsVec2 = std::is_same_v<typename T::TypeId, internal::IsVec2Helper_>;

template<typename ArgX, typename ArgY = ArgX>
struct Vec2
{
  using TypeId = internal::IsVec2Helper_;
  using X = ArgX;
  using Y = ArgY;

  X x;
  Y y;

  [[nodiscard]] constexpr Vec2() noexcept
    : x()
    , y()
  {
  }

  [[nodiscard]] constexpr Vec2(auto x, auto y) noexcept
    : x(static_cast<X>(x))
    , y(static_cast<Y>(y))
  {
  }

  [[nodiscard]] constexpr Vec2(IsVec2 auto rhs) noexcept // NOLINT(*-explicit-conversions)
    : x(static_cast<X>(rhs.x))
    , y(static_cast<Y>(rhs.y))
  {
  }

  constexpr Vec2& operator=(IsVec2 auto rhs) noexcept
  {
    x = static_cast<X>(rhs.x);
    y = static_cast<Y>(rhs.y);
    return *this;
  }

  [[nodiscard]] constexpr auto operator+(IsVec2 auto rhs) const noexcept
  {
    const auto x_ = x + rhs.x;
    const auto y_ = y + rhs.y;
    return Vec2<decltype(x_), decltype(y_)>{ x_, y_ };
  }

  constexpr Vec2& operator+=(IsVec2 auto rhs) noexcept
  {
    return *this = *this + rhs;
  }

  [[nodiscard]] constexpr auto operator-(IsVec2 auto rhs) const noexcept
  {
    const auto x_ = x - rhs.x;
    const auto y_ = y - rhs.y;
    return Vec2<decltype(x_), decltype(y_)>{ x_, y_ };
  }

  constexpr Vec2& operator-=(IsVec2 auto rhs) noexcept
  {
    return *this = *this - rhs;
  }

  [[nodiscard]] constexpr auto operator*(auto scalar) const noexcept
  {
    const auto x_ = x * scalar;
    const auto y_ = y * scalar;
    return Vec2<decltype(x_), decltype(y_)>{ x_, y_ };
  }

  constexpr Vec2& operator*=(auto scalar) noexcept
  {
    return *this = *this * scalar;
  }

  [[nodiscard]] constexpr auto operator/(auto scalar) const noexcept
  {
    const auto x_ = x / scalar;
    const auto y_ = y / scalar;
    return Vec2<decltype(x_), decltype(y_)>{ x_, y_ };
  }

  constexpr Vec2& operator/=(auto scalar) noexcept
  {
    return *this = *this / scalar;
  }

  [[nodiscard]] constexpr auto operator-() const noexcept
  {
    const auto x_ = -x;
    const auto y_ = -y;
    return Vec2<decltype(x_), decltype(y_)>{ x_, y_ };
  }

  [[nodiscard]] constexpr bool operator==(IsVec2 auto rhs) const noexcept
  {
    return x == rhs.x && y == rhs.y;
  }

  [[nodiscard]] constexpr bool operator!=(IsVec2 auto rhs) const noexcept
  {
    return !(*this == rhs);
  }
};

// Non-member scalar multiplication
[[nodiscard]] constexpr auto
operator*(auto lhs, IsVec2 auto rhs) noexcept
{
  const auto x_ = lhs * rhs.x;
  const auto y_ = lhs * rhs.y;
  return Vec2<decltype(x_), decltype(y_)>{ x_, y_ };
}

[[nodiscard]] constexpr auto
Abs(IsVec2 auto v) noexcept
{
  const auto x_ = v.x < 0 ? -v.x : v.x;
  const auto y_ = v.y < 0 ? -v.y : v.y;
  return Vec2<decltype(x_), decltype(y_)>{ x_, y_ };
}

[[nodiscard]] constexpr auto
Dot(IsVec2 auto lhs, IsVec2 auto rhs) noexcept
{
  return lhs.x * rhs.x + lhs.y * rhs.y;
}

[[nodiscard]] constexpr auto
Length(IsVec2 auto v, auto Sqrt) noexcept
{
  return Sqrt(Dot(v, v));
}

[[nodiscard]] constexpr auto
Normalize(IsVec2 auto v, auto Sqrt) noexcept
{
  return v / Length(v, Sqrt);
}
