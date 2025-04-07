#pragma once

#include <type_traits>

// clang-format off
namespace internal{enum class IsVec3Helper_{};}
// clang-format on

template<typename T>
concept IsVec3 = std::is_same_v<typename T::TypeId, internal::IsVec3Helper_>;

template<typename ArgX, typename ArgY = ArgX, typename ArgZ = ArgX>
struct Vec3
{
  using TypeId = internal::IsVec3Helper_;
  using X = ArgX;
  using Y = ArgY;
  using Z = ArgZ;

  X x;
  Y y;
  Z z;

  [[nodiscard]] constexpr Vec3() noexcept
    : x()
    , y()
    , z()
  {
  }

  [[nodiscard]] constexpr Vec3(auto x, auto y, auto z) noexcept
    : x(static_cast<X>(x))
    , y(static_cast<Y>(y))
    , z(static_cast<Z>(z))
  {
  }

  [[nodiscard]] constexpr Vec3(IsVec3 auto rhs) noexcept // NOLINT(*-explicit-conversions)
    : x(static_cast<X>(rhs.x))
    , y(static_cast<Y>(rhs.y))
    , z(static_cast<Z>(rhs.z))
  {
  }

  constexpr Vec3& operator=(IsVec3 auto rhs) noexcept
  {
    x = static_cast<X>(rhs.x);
    y = static_cast<Y>(rhs.y);
    z = static_cast<Z>(rhs.z);
    return *this;
  }

  [[nodiscard]] constexpr auto operator+(IsVec3 auto rhs) const noexcept
  {
    const auto x_ = x + rhs.x;
    const auto y_ = y + rhs.y;
    const auto z_ = z + rhs.z;
    return Vec3<decltype(x_), decltype(y_), decltype(z_)>{ x_, y_, z_ };
  }

  constexpr Vec3& operator+=(IsVec3 auto rhs) noexcept
  {
    return *this = *this + rhs;
  }

  [[nodiscard]] constexpr auto operator-(IsVec3 auto rhs) const noexcept
  {
    const auto x_ = x - rhs.x;
    const auto y_ = y - rhs.y;
    const auto z_ = z - rhs.z;
    return Vec3<decltype(x_), decltype(y_), decltype(z_)>{ x_, y_, z_ };
  }

  constexpr Vec3& operator-=(IsVec3 auto rhs) noexcept
  {
    return *this = *this - rhs;
  }

  [[nodiscard]] constexpr auto operator*(auto scalar) const noexcept
  {
    const auto x_ = x * scalar;
    const auto y_ = y * scalar;
    const auto z_ = z * scalar;
    return Vec3<decltype(x_), decltype(y_), decltype(z_)>{ x_, y_, z_ };
  }

  constexpr Vec3& operator*=(auto scalar) noexcept
  {
    return *this = *this * scalar;
  }

  [[nodiscard]] constexpr auto operator/(auto scalar) const noexcept
  {
    const auto x_ = x / scalar;
    const auto y_ = y / scalar;
    const auto z_ = z / scalar;
    return Vec3<decltype(x_), decltype(y_), decltype(z_)>{ x_, y_, z_ };
  }

  constexpr Vec3& operator/=(auto scalar) noexcept
  {
    return *this = *this / scalar;
  }

  [[nodiscard]] constexpr auto operator-() const noexcept
  {
    const auto x_ = -x;
    const auto y_ = -y;
    const auto z_ = -z;
    return Vec3<decltype(x_), decltype(y_), decltype(z_)>{ x_, y_, z_ };
  }

  [[nodiscard]] constexpr bool operator==(IsVec3 auto rhs) const noexcept
  {
    return x == rhs.x && y == rhs.y && z == rhs.z;
  }

  [[nodiscard]] constexpr bool operator!=(IsVec3 auto rhs) const noexcept
  {
    return !(*this == rhs);
  }
};

[[nodiscard]] constexpr auto
operator*(auto lhs, IsVec3 auto rhs) noexcept
{
  const auto x_ = lhs * rhs.x;
  const auto y_ = lhs * rhs.y;
  const auto z_ = lhs * rhs.z;
  return Vec3<decltype(x_), decltype(y_), decltype(z_)>{ x_, y_, z_ };
}

[[nodiscard]] constexpr auto
Abs(IsVec3 auto v) noexcept
{
  const auto x_ = v.x < 0 ? -v.x : v.x;
  const auto y_ = v.y < 0 ? -v.y : v.y;
  const auto z_ = v.z < 0 ? -v.z : v.z;
  return Vec3<decltype(x_), decltype(y_), decltype(z_)>{ x_, y_, z_ };
}

[[nodiscard]] constexpr auto
Dot(IsVec3 auto lhs, IsVec3 auto rhs) noexcept
{
  return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

[[nodiscard]] constexpr auto
Length(IsVec3 auto v, auto Sqrt) noexcept
{
  return Sqrt(Dot(v, v));
}

[[nodiscard]] constexpr auto
Normalize(IsVec3 auto v, auto Sqrt) noexcept
{
  return v / Length(v, Sqrt);
}
