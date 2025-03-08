#pragma once

#include <type_traits>

namespace base {

template<typename X, typename Y = X, typename Z = X, typename W = X>
struct Vec4
{
public:
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

  template<typename X_, typename Y_, typename Z_, typename W_>
  [[nodiscard]] constexpr Vec4(X_ x, Y_ y, Z_ z, W_ w) noexcept
    : x(x)
    , y(y)
    , z(z)
    , w(w)
  {
  }

  template<typename X_, typename Y_, typename Z_, typename W_>
  [[nodiscard]] constexpr Vec4(Vec4<X_, Y_, Z_, W_> other) noexcept // NOLINT(*-explicit-conversions)
    : x(other.x)
    , y(other.y)
    , z(other.z)
    , w(other.w)
  {
  }

  template<typename X_, typename Y_, typename Z_, typename W_>
  [[nodiscard]] constexpr Vec4<X, Y, Z, W>& operator=(Vec4<X_, Y_, Z_, W_> other) noexcept
  {
    if constexpr (std::is_same_v<X, X_> && std::is_same_v<Y, Y_> && std::is_same_v<Z, Z_> && std::is_same_v<W, W_>) {
      if (this == &other) {
        return *this;
      }
    }

    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;
    return *this;
  }

  template<typename X_, typename Y_, typename Z_, typename W_>
  [[nodiscard]] constexpr auto operator+(Vec4<X_, Y_, Z_, W_> other) const noexcept
  {
    const auto x_ = x + other.x;
    const auto y_ = y + other.y;
    const auto z_ = z + other.z;
    const auto w_ = w + other.w;
    return Vec4<decltype(x_), decltype(y_), decltype(z_), decltype(w_)>(x_, y_, z_, w_);
  }

  template<typename X_, typename Y_, typename Z_, typename W_>
  constexpr Vec4<X, Y, Z, W>& operator+=(const Vec4<X_, Y_, Z_, W_>& other) noexcept
  {
    x += other.x;
    y += other.y;
    z += other.z;
    w += other.w;
    return *this;
  }

  template<typename X_, typename Y_, typename Z_, typename W_>
  [[nodiscard]] constexpr auto operator-(const Vec4<X_, Y_, Z_, W_>& other) const noexcept
  {
    const auto x_ = x - other.x;
    const auto y_ = y - other.y;
    const auto z_ = z - other.z;
    const auto w_ = w - other.w;
    return Vec4<decltype(x_), decltype(y_), decltype(z_), decltype(w_)>(x_, y_, z_, w_);
  }

  template<typename X_, typename Y_, typename Z_, typename W_>
  [[nodiscard]] constexpr Vec4<X, Y, Z, W>& operator-=(const Vec4<X_, Y_, Z_, W_>& other) noexcept
  {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    w -= other.w;
    return *this;
  }

  template<typename S>
  [[nodiscard]] constexpr auto operator*(S s) const noexcept
  {
    const auto x_ = x * s;
    const auto y_ = y * s;
    const auto z_ = z * s;
    const auto w_ = w * s;
    return Vec4<decltype(x_), decltype(y_), decltype(z_), decltype(w_)>(x_, y_, z_, w_);
  }

  template<typename S>
  [[nodiscard]] constexpr Vec4<X, Y, Z, W>& operator*=(S s) noexcept
  {
    x *= s;
    y *= s;
    z *= s;
    w *= s;
    return *this;
  }

  template<typename S>
  [[nodiscard]] constexpr auto operator/(S s) const noexcept
  {
    const auto x_ = x / s;
    const auto y_ = y / s;
    const auto z_ = z / s;
    const auto w_ = w / s;
    return Vec4<decltype(x_), decltype(y_), decltype(z_), decltype(w_)>(x_, y_, z_, w_);
  }

  template<typename S>
  [[nodiscard]] constexpr Vec4<X, Y, Z, W>& operator/=(S s) noexcept
  {
    x /= s;
    y /= s;
    z /= s;
    w /= s;
    return *this;
  }

  [[nodiscard]] constexpr auto operator-() const noexcept
  {
    const auto x_ = -x;
    const auto y_ = -y;
    const auto z_ = -z;
    const auto w_ = -w;
    return Vec4<decltype(x_), decltype(y_), decltype(z_), decltype(w_)>(x_, y_, z_, w_);
  }

  template<typename X_, typename Y_, typename Z_, typename W_>
  [[nodiscard]] constexpr bool operator==(const Vec4<X_, Y_, Z_, W_>& other) const noexcept
  {
    return x == other.x && y == other.y && z == other.z && w == other.w;
  }

  template<typename X_, typename Y_, typename Z_, typename W_>
  [[nodiscard]] constexpr bool operator!=(const Vec4<X_, Y_, Z_, W_>& other) const noexcept
  {
    return x != other.x || y != other.y || z != other.z || w != other.w;
  }
};

template<typename S, typename X, typename Y, typename Z, typename W>
[[nodiscard]] constexpr auto
operator*(S s, Vec4<X, Y, Z, W> v) noexcept
{
  const auto x_ = s * v.x;
  const auto y_ = s * v.y;
  const auto z_ = s * v.z;
  const auto w_ = s * v.w;
  return Vec4<decltype(x_), decltype(y_), decltype(z_), decltype(w_)>(x_, y_, z_, w_);
}

template<typename X, typename Y, typename Z, typename W>
[[nodiscard]] constexpr auto
Abs(Vec4<X, Y, Z, W> v) noexcept
{
  const auto x_ = Abs(v.x);
  const auto y_ = Abs(v.y);
  const auto z_ = Abs(v.z);
  const auto w_ = Abs(v.w);
  return Vec4<decltype(x_), decltype(y_), decltype(z_), decltype(w_)>{ x_, y_, z_, w_ };
}

template<typename X0, typename Y0, typename Z0, typename W0, typename X1, typename Y1, typename Z1, typename W1>
[[nodiscard]] constexpr auto
Dot(Vec4<X0, Y0, Z0, W0> v0, Vec4<X1, Y1, Z1, W1> v1) noexcept
{
  return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z + v0.w * v1.w;
}

template<typename X, typename Y, typename Z, typename W, typename Sqrt>
[[nodiscard]] constexpr auto
Length(Vec4<X, Y, Z, W> v, Sqrt sqrt = std::sqrt) noexcept
{
  return sqrt(Dot(v, v));
}

template<typename X, typename Y, typename Z, typename W>
[[nodiscard]] constexpr auto
Normalize(Vec4<X, Y, Z, W> v) noexcept
{
  return v / Length(v);
}

}
