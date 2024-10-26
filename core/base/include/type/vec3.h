#pragma once

#include <type_traits>

template<typename X, typename Y = X, typename Z = X>
class Vec3
{
public:
  X x;
  Y y;
  Z z;

  [[nodiscard]] constexpr inline Vec3() noexcept
    : x()
    , y()
    , z()
  {
  }

  template<typename X_, typename Y_, typename Z_>
  [[nodiscard]] constexpr inline Vec3(X_ x, Y_ y, Z_ z) noexcept
    : x(x)
    , y(y)
    , z(z)
  {
  }

#pragma clang diagnostic push
#pragma ide diagnostic ignored "google-explicit-constructor"
  template<typename X_, typename Y_, typename Z_>
  [[nodiscard]] constexpr inline Vec3(Vec3<X_, Y_, Z_> other) noexcept
    : x(other.x)
    , y(other.y)
    , z(other.z)
  {
  }
#pragma clang diagnostic pop

  template<typename X_, typename Y_, typename Z_>
  [[nodiscard]] constexpr inline Vec3<X, Y, Z>& operator=(Vec3<X_, Y_, Z_> other) noexcept
  {
    if constexpr (std::is_same_v<X, X_> && std::is_same_v<Y, Y_> && std::is_same_v<Z, Z_>)
      if (this == &other)
        return *this;

    x = other.x;
    y = other.y;
    z = other.z;
    return *this;
  }

  template<typename X_, typename Y_, typename Z_>
  [[nodiscard]] constexpr inline auto operator+(Vec3<X_, Y_, Z_> other) const noexcept
  {
    const auto x_ = x + other.x;
    const auto y_ = y + other.y;
    const auto z_ = z + other.z;
    return Vec3<decltype(x_), decltype(y_), decltype(z_)>(x_, y_, z_);
  }

  template<typename X_, typename Y_, typename Z_>
  constexpr inline Vec3<X, Y, Z>& operator+=(const Vec3<X_, Y_, Z_>& other) noexcept
  {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
  }

  template<typename X_, typename Y_, typename Z_>
  [[nodiscard]] constexpr inline auto operator-(const Vec3<X_, Y_, Z_>& other) const noexcept
  {
    const auto x_ = x - other.x;
    const auto y_ = y - other.y;
    const auto z_ = z - other.z;
    return Vec3<decltype(x_), decltype(y_), decltype(z_)>(x_, y_, z_);
  }

  template<typename X_, typename Y_, typename Z_>
  [[nodiscard]] constexpr inline Vec3<X, Y, Z>& operator-=(const Vec3<X_, Y_, Z_>& other) noexcept
  {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
  }

  template<typename S>
  [[nodiscard]] constexpr inline auto operator*(S s) const noexcept
  {
    const auto x_ = x * s;
    const auto y_ = y * s;
    const auto z_ = z * s;
    return Vec3<decltype(x_), decltype(y_), decltype(z_)>(x_, y_, z_);
  }

  template<typename S>
  [[nodiscard]] constexpr inline Vec3<X, Y, Z>& operator*=(S s) noexcept
  {
    x *= s;
    y *= s;
    z *= s;
    return *this;
  }

  template<typename S>
  [[nodiscard]] constexpr inline auto operator/(S s) const noexcept
  {
    const auto x_ = x / s;
    const auto y_ = y / s;
    const auto z_ = z / s;
    return Vec3<decltype(x_), decltype(y_), decltype(z_)>(x_, y_, z_);
  }

  template<typename S>
  [[nodiscard]] constexpr inline Vec3<X, Y, Z>& operator/=(S s) noexcept
  {
    x /= s;
    y /= s;
    z /= s;
    return *this;
  }

  [[nodiscard]] constexpr inline auto operator-() const noexcept
  {
    const auto x_ = -x;
    const auto y_ = -y;
    const auto z_ = -z;
    return Vec3<decltype(x_), decltype(y_), decltype(z_)>(x_, y_, z_);
  }

  template<typename X_, typename Y_, typename Z_>
  [[nodiscard]] constexpr inline bool operator==(const Vec3<X_, Y_, Z_>& other) const noexcept
  {
    return x == other.x && y == other.y && z == other.z;
  }

  template<typename X_, typename Y_, typename Z_>
  [[nodiscard]] constexpr inline bool operator!=(const Vec3<X_, Y_, Z_>& other) const noexcept
  {
    return x != other.x || y != other.y || z != other.z;
  }
};

template<typename S, typename X, typename Y, typename Z>
[[nodiscard]] constexpr inline auto
operator*(S s, Vec3<X, Y, Z> v) noexcept
{
  const auto x_ = s * v.x;
  const auto y_ = s * v.y;
  const auto z_ = s * v.z;
  return Vec3<decltype(x_), decltype(y_), decltype(z_)>(x_, y_, z_);
}

template<typename X, typename Y, typename Z>
[[nodiscard]] constexpr inline auto
Abs(Vec3<X, Y, Z> v) noexcept
{
  const auto x_ = Abs(v.x);
  const auto y_ = Abs(v.y);
  const auto z_ = Abs(v.z);
  return Vec3<decltype(x_), decltype(y_), decltype(z_)>{ x_, y_, z_ };
}

template<typename X0, typename Y0, typename Z0, typename X1, typename Y1, typename Z1>
[[nodiscard]] constexpr inline auto
Dot(Vec3<X0, Y0, Z0> v0, Vec3<X1, Y1, Z1> v1) noexcept
{
  return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z;
}

template<typename X, typename Y, typename Z>
[[nodiscard]] constexpr inline auto
Length(Vec3<X, Y, Z> v) noexcept
{
  return Sqrt(Dot(v, v));
}

template<typename X, typename Y, typename Z>
[[nodiscard]] constexpr inline auto
Normalize(Vec3<X, Y, Z> v) noexcept
{
  return v / Length(v);
}
