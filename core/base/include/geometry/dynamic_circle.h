#pragma once

#include "./aabb.h"
#include "./circle.h"

#include "../base.h"

namespace base {

template<typename Position, typename Radius, typename Velocity>
struct DynamicCircle
{
  Vec2<Position> p;
  Radius r;
  Vec2<Velocity> v;

  constexpr inline auto AABB() const
  {
    const auto min_x = p.x - r + std::min<decltype(v.x)>(v.x, static_cast<decltype(v.x)>(c0));
    const auto min_y = p.y - r + std::min<decltype(v.y)>(v.y, static_cast<decltype(v.y)>(c0));
    const auto max_x = p.x + r + std::max<decltype(v.x)>(v.x, static_cast<decltype(v.x)>(c0));
    const auto max_y = p.y + r + std::max<decltype(v.y)>(v.y, static_cast<decltype(v.y)>(c0));
    return base::AABB{ min_x, min_y, max_x, max_y };
  }

  constexpr inline auto R45BB() const
  {
    const auto vx_ = v.x - v.y;
    const auto vy_ = v.x + v.y;
    const auto x_ = p.x - p.y;
    const auto y_ = p.x + p.y;
    const auto r_ = r * sqrt2ub;
    const auto min_x = x_ - r_ + std::min<decltype(vx_)>(vx_, static_cast<decltype(v.x)>(c0));
    const auto min_y = y_ - r_ + std::min<decltype(vy_)>(vy_, static_cast<decltype(v.y)>(c0));
    const auto max_x = x_ + r_ + std::max<decltype(vx_)>(vx_, static_cast<decltype(v.x)>(c0));
    const auto max_y = y_ + r_ + std::max<decltype(vy_)>(vy_, static_cast<decltype(v.y)>(c0));
    return base::R45BB{ min_x, min_y, max_x, max_y };
  }
};

// clang-format off
template<typename Position0, typename Radius0, typename Velocity0,
         typename Position1, typename Radius1, typename Velocity1>
constexpr inline bool
Overlap(DynamicCircle<Position0, Radius0, Velocity0> d0, DynamicCircle<Position1, Radius1, Velocity1> d1) noexcept
{
  // Equation to solve for t:
  // |(d0.p + t * d0.v) - (d1.p + t * d1.v)| <= d0.r + d1.r
  // <=> (dvv)t^2 + (2dpv)t + dpp <= x*x

  const auto x = d1.r + d0.r;
  const auto xx = (x * x);

  // *** CHECK FOR COLLISION AT t=0 ***

  const auto dp = d1.p - d0.p;
  const auto dpp = Dot(dp, dp);
  const auto c = dpp;

  if (c <= xx)
    return true; // colliding at t=0

  // *** CHECK FOR COLLISION AT t=1 ***

  const auto v0_ = (decltype(d0.p){ d0.p + d0.v }) - d0.p;
  const auto v1_ = (decltype(d1.p){ d1.p + d1.v }) - d1.p;
  const auto dv = v1_ - v0_;
  // ensure the velocity is accurate with roundings
  // const auto dv = (dt * d1.v) - (dt * d0.v);

  const auto dpv = Dot(dp, dv);
  const auto dvv = Dot(dv, dv);
  const auto a = dvv;
  const auto b = dpv + dpv;

  if (a + b + c <= xx)
    return true; // colliding at t=1

  // *** ANALYSE DERIVATIVE FOR CLOSEST POINT ***
  // 2at + b = 0 <=> t = -b / 2a

  if (b > c0)
    return false; // Closest Point at t<0

  const auto a2 = a + a;
  if (-b > a2)
    return false; // Closest Point at t>1

  if (a == c0) {
    if (b == c0) // Constant Equation
      return c <= xx;
    // Linear Equation
    // 0 = bt + c <=> t_min = -c / b
    const auto t_min = -c / b;
    return t_min < c1 && t_min > c0;
  }

  // Closest Point at 0 < t < 1:
  // t = -b / (a + a) <=> c - (bb / a4)
  return c - (b * b) / (a2 + a2) <= xx;
}
// clang-format on

// clang-format off
template<typename Position0, typename Radius0,
         typename Position1, typename Radius1, typename Velocity1>
constexpr inline bool
Overlap(Circle<Position0, Radius0> d0, DynamicCircle<Position1, Radius1, Velocity1> d1) noexcept
{
  // Equation to solve for t:
  // |d0.p - (d1.p + t * d1.v)| <= d0.r + d1.r
  // <=> (dvv)t^2 + (2dpv)t + dpp <= x*x

  const auto x = d1.r + d0.r;
  const auto xx = (x * x);

  // *** CHECK FOR COLLISION AT t=0 ***

  const auto dp = d1.p - d0.p;
  const auto dpp = Dot(dp, dp);
  const auto c = dpp;

  if (c <= xx)
    return true; // colliding at t=0

  // *** CHECK FOR COLLISION AT t=1 ***

  const auto dv = (decltype(d1.p){ d1.p + d1.v }) - d1.p;
  // ensure the velocity is accurate with roundings
  // const auto dv = dt * d1.v;

  const auto dpv = Dot(dp, dv);
  const auto dvv = Dot(dv, dv);
  const auto a = dvv;
  const auto b = dpv + dpv;

  if (a + b + c <= xx)
    return true; // colliding at t=1

  // *** ANALYSE DERIVATIVE FOR CLOSEST POINT ***
  // 2at + b = 0 <=> t = -b / 2a

  if (b > c0)
    return false; // Closest Point at t<0

  const auto a2 = a + a;
  if (-b > a2)
    return false; // Closest Point at t>1

  if (a == c0) {
    if (b == c0) // Constant Equation
      return c <= xx;
    // Linear Equation
    // 0 = bt + c <=> t_min = -c / b
    const auto t_min = -c / b;
    return t_min < c1 && t_min > c0;
  }

  // Closest Point at 0 < t < 1:
  // t = -b / (a + a) <=> c - (bb / a4)
  return c - (b * b) / (a2 + a2) <= xx;
}
// clang-format on

// clang-format off
template<typename Position0, typename Radius0, typename Velocity0,
         typename Position1, typename Radius1>
constexpr inline bool
Overlap(DynamicCircle<Position0, Radius0, Velocity0> d0, Circle<Position1, Radius1> d1) noexcept
{
  return Overlap(d1,d0);
}
// clang-format on

template<typename Position, typename Radius, typename Velocity>
constexpr inline auto
Advance(DynamicCircle<Position, Radius, Velocity> dynamic) noexcept
{
  const auto p_ = dynamic.p + dynamic.v;
  const auto r_ = dynamic.r;
  static_assert(std::is_same_v<decltype(p_.x), decltype(p_.y)>);
  return Circle<decltype(p_.x), decltype(r_)>{ p_, r_ };
}

template<typename Position, typename Radius, typename Velocity>
constexpr inline auto
Advance(DynamicCircle<Position, Radius, Velocity> dynamic, auto dt) noexcept
{
  const auto p_ = dynamic.p + dt * dynamic.v;
  const auto r_ = dynamic.r;
  static_assert(std::is_same_v<decltype(p_.x), decltype(p_.y)>);
  return Circle<decltype(p_.x), decltype(r_)>{ p_, r_ };
}

}
