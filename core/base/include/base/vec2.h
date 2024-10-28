#pragma once

#include <type_traits>

namespace base {

template<typename X, typename Y = X>
class Vec2
{
public:
  X x;
  Y y;

  [[nodiscard]] constexpr inline Vec2() noexcept
    : x()
    , y()
  {
  }

  template<typename X_, typename Y_>
  [[nodiscard]] constexpr inline Vec2(X_ x, Y_ y) noexcept
    : x(x)
    , y(y)
  {
  }

#pragma clang diagnostic push
#pragma ide diagnostic ignored "google-explicit-constructor"
  template<typename X_, typename Y_>
  [[nodiscard]] constexpr inline Vec2(Vec2<X_, Y_> other) noexcept
    : x(other.x)
    , y(other.y)
  {
  }
#pragma clang diagnostic pop

  template<typename X_, typename Y_>
  [[nodiscard]] constexpr inline Vec2<X, Y>& operator=(Vec2<X_, Y_> other) noexcept
  {
    if constexpr (std::is_same_v<X, X_> && std::is_same_v<Y, Y_>)
      if (this == &other)
        return *this;

    x = other.x;
    y = other.y;
    return *this;
  }

  template<typename X_, typename Y_>
  [[nodiscard]] constexpr inline auto operator+(Vec2<X_, Y_> other) const noexcept
  {
    const auto x_ = x + other.x;
    const auto y_ = y + other.y;
    return Vec2<decltype(x_), decltype(y_)>(x_, y_);
  }

  template<typename X_, typename Y_>
  constexpr inline Vec2<X, Y>& operator+=(const Vec2<X_, Y_>& other) noexcept
  {
    x += other.x;
    y += other.y;
    return *this;
  }

  template<typename X_, typename Y_>
  [[nodiscard]] constexpr inline auto operator-(const Vec2<X_, Y_>& other) const noexcept
  {
    const auto x_ = x - other.x;
    const auto y_ = y - other.y;
    return Vec2<decltype(x_), decltype(y_)>(x_, y_);
  }

  template<typename X_, typename Y_>
  [[nodiscard]] constexpr inline Vec2<X, Y>& operator-=(const Vec2<X_, Y_>& other) noexcept
  {
    x -= other.x;
    y -= other.y;
    return *this;
  }

  template<typename S>
  [[nodiscard]] constexpr inline auto operator*(S s) const noexcept
  {
    const auto x_ = x * s;
    const auto y_ = y * s;
    return Vec2<decltype(x_), decltype(y_)>(x_, y_);
  }

  template<typename S>
  [[nodiscard]] constexpr inline Vec2<X, Y>& operator*=(S s) noexcept
  {
    x *= s;
    y *= s;
    return *this;
  }

  template<typename S>
  [[nodiscard]] constexpr inline auto operator/(S s) const noexcept
  {
    const auto x_ = x / s;
    const auto y_ = y / s;
    return Vec2<decltype(x_), decltype(y_)>(x_, y_);
  }

  template<typename S>
  [[nodiscard]] constexpr inline Vec2<X, Y>& operator/=(S s) noexcept
  {
    x /= s;
    y /= s;
    return *this;
  }

  [[nodiscard]] constexpr inline auto operator-() const noexcept
  {
    const auto x_ = -x;
    const auto y_ = -y;
    return Vec2<decltype(x_), decltype(y_)>(x_, y_);
  }

  template<typename X_, typename Y_>
  [[nodiscard]] constexpr inline bool operator==(const Vec2<X_, Y_>& other) const noexcept
  {
    return x == other.x && y == other.y;
  }

  template<typename X_, typename Y_>
  [[nodiscard]] constexpr inline bool operator!=(const Vec2<X_, Y_>& other) const noexcept
  {
    return x != other.x && y != other.y;
  }
};

template<typename S, typename X, typename Y>
[[nodiscard]] constexpr inline auto
operator*(S s, Vec2<X, Y> v) noexcept
{
  const auto x_ = s * v.x;
  const auto y_ = s * v.y;
  return Vec2<decltype(x_), decltype(y_)>(x_, y_);
}

template<typename X, typename Y>
[[nodiscard]] constexpr inline auto
Abs(Vec2<X, Y> v) noexcept
{
  const auto x_ = Abs(v.x);
  const auto y_ = Abs(v.y);
  return Vec2<decltype(x_), decltype(y_)>{ x_, y_ };
}

template<typename X0, typename Y0, typename X1, typename Y1>
[[nodiscard]] constexpr inline auto
Dot(Vec2<X0, Y0> v0, Vec2<X1, Y1> v1) noexcept
{
  return v0.x * v1.x + v0.y * v1.y;
}

template<typename X, typename Y>
[[nodiscard]] constexpr inline auto
Length(Vec2<X, Y> v) noexcept
{
  return cnl::sqrt(Dot(v, v));
}

template<typename X, typename Y>
[[nodiscard]] constexpr inline auto
Normalize(Vec2<X, Y> v) noexcept
{
  return v / Length(v);
}

}
