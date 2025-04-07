#pragma once

#include <type_traits>

// clang-format off
namespace internal{enum class IsVec4Helper_{};}
// clang-format on

template<typename T>
concept IsVec4 = std::is_same_v<typename T::TypeId, internal::IsVec4Helper_>;

template<typename ArgX, typename ArgY = ArgX, typename ArgZ = ArgX, typename ArgW = ArgX>
struct Vec4
{
  using TypeId = internal::IsVec4Helper_;
  using X = ArgX;
  using Y = ArgY;
  using Z = ArgZ;
  using W = ArgW;

  X x;
  Y y;
  Z z;
  W w;

  [[nodiscard]] constexpr Vec4() noexcept
    : x()
    , y()
    , z()
    , w()
  {
  }

  [[nodiscard]] constexpr Vec4(auto x, auto y, auto z, auto w) noexcept
    : x(static_cast<X>(x))
    , y(static_cast<Y>(y))
    , z(static_cast<Z>(z))
    , w(static_cast<W>(w))
  {
  }

  [[nodiscard]] constexpr Vec4(IsVec4 auto rhs) noexcept // NOLINT(*-explicit-conversions)
    : x(static_cast<X>(rhs.x))
    , y(static_cast<Y>(rhs.y))
    , z(static_cast<Z>(rhs.z))
    , w(static_cast<W>(rhs.w))
  {
  }

  constexpr Vec4& operator=(IsVec4 auto rhs) noexcept
  {
    x = static_cast<X>(rhs.x);
    y = static_cast<Y>(rhs.y);
    z = static_cast<Z>(rhs.z);
    w = static_cast<W>(rhs.w);
    return *this;
  }

  [[nodiscard]] constexpr auto operator+(IsVec4 auto rhs) const noexcept
  {
    const auto x_ = x + rhs.x;
    const auto y_ = y + rhs.y;
    const auto z_ = z + rhs.z;
    const auto w_ = w + rhs.w;
    return Vec4<decltype(x_), decltype(y_), decltype(z_), decltype(w_)>{ x_, y_, z_, w_ };
  }

  constexpr Vec4& operator+=(IsVec4 auto rhs) noexcept
  {
    return *this = *this + rhs;
  }

  [[nodiscard]] constexpr auto operator-(IsVec4 auto rhs) const noexcept
  {
    const auto x_ = x - rhs.x;
    const auto y_ = y - rhs.y;
    const auto z_ = z - rhs.z;
    const auto w_ = w - rhs.w;
    return Vec4<decltype(x_), decltype(y_), decltype(z_), decltype(w_)>{ x_, y_, z_, w_ };
  }

  constexpr Vec4& operator-=(IsVec4 auto rhs) noexcept
  {
    return *this = *this - rhs;
  }

  [[nodiscard]] constexpr auto operator*(auto scalar) const noexcept
  {
    const auto x_ = x * scalar;
    const auto y_ = y * scalar;
    const auto z_ = z * scalar;
    const auto w_ = w * scalar;
    return Vec4<decltype(x_), decltype(y_), decltype(z_), decltype(w_)>{ x_, y_, z_, w_ };
  }

  constexpr Vec4& operator*=(auto scalar) noexcept
  {
    return *this = *this * scalar;
  }

  [[nodiscard]] constexpr auto operator/(auto scalar) const noexcept
  {
    const auto x_ = x / scalar;
    const auto y_ = y / scalar;
    const auto z_ = z / scalar;
    const auto w_ = w / scalar;
    return Vec4<decltype(x_), decltype(y_), decltype(z_), decltype(w_)>{ x_, y_, z_, w_ };
  }

  constexpr Vec4& operator/=(auto scalar) noexcept
  {
    return *this = *this / scalar;
  }

  [[nodiscard]] constexpr auto operator-() const noexcept
  {
    const auto x_ = -x;
    const auto y_ = -y;
    const auto z_ = -z;
    const auto w_ = -w;
    return Vec4<decltype(x_), decltype(y_), decltype(z_), decltype(w_)>{ x_, y_, z_, w_ };
  }

  [[nodiscard]] constexpr bool operator==(IsVec4 auto rhs) const noexcept
  {
    return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w;
  }

  [[nodiscard]] constexpr bool operator!=(IsVec4 auto rhs) const noexcept
  {
    return !(*this == rhs);
  }
};

[[nodiscard]] constexpr auto
operator*(auto lhs, IsVec4 auto rhs) noexcept
{
  const auto x_ = lhs * rhs.x;
  const auto y_ = lhs * rhs.y;
  const auto z_ = lhs * rhs.z;
  const auto w_ = lhs * rhs.w;
  return Vec4<decltype(x_), decltype(y_), decltype(z_), decltype(w_)>{ x_, y_, z_, w_ };
}

[[nodiscard]] constexpr auto
Abs(IsVec4 auto v) noexcept
{
  const auto x_ = v.x < 0 ? -v.x : v.x;
  const auto y_ = v.y < 0 ? -v.y : v.y;
  const auto z_ = v.z < 0 ? -v.z : v.z;
  const auto w_ = v.w < 0 ? -v.w : v.w;
  return Vec4<decltype(x_), decltype(y_), decltype(z_), decltype(w_)>{ x_, y_, z_, w_ };
}

[[nodiscard]] constexpr auto
Dot(IsVec4 auto lhs, IsVec4 auto rhs) noexcept
{
  return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
}

[[nodiscard]] constexpr auto
Length(IsVec4 auto v, auto Sqrt) noexcept
{
  return Sqrt(Dot(v, v));
}

[[nodiscard]] constexpr auto
Normalize(IsVec4 auto v, auto Sqrt) noexcept
{
  return v / Length(v, Sqrt);
}
