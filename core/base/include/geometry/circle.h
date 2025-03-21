#pragma once

#include "../base.h"

#include "./aabb.h"

namespace base {

template<typename Position, typename Radius>
struct Circle
{
  Vec2<Position> p;
  Radius r;

  [[nodiscard]] constexpr auto AABB() const noexcept
  {
    const auto min_x = p.x - r;
    const auto min_y = p.y - r;
    const auto max_x = p.x + r;
    const auto max_y = p.y + r;
    return base::AABB{ min_x, min_y, max_x, max_y };
  }

  [[nodiscard]] constexpr auto R45BB(auto sqrt2ub = double_sqrt2ub) const noexcept
  {
    const auto x_ = p.x - p.y;
    const auto y_ = p.x + p.y;
    const auto r_ = r * sqrt2ub;

    const auto min_x = x_ - r_;
    const auto min_y = y_ - r_;
    const auto max_x = x_ + r_;
    const auto max_y = y_ + r_;
    return base::R45BB{ min_x, min_y, max_x, max_y };
  }
};

template<typename PositionA, typename RadiusA, typename PositionB, typename RadiusB>
[[nodiscard]] constexpr bool
Overlap(Circle<PositionA, RadiusA> a, Circle<PositionB, RadiusB> b) noexcept
{
  const auto x = b.r + a.r;
  const auto d = b.p - a.p;
  return Dot(d, d) <= x * x;
}

template<typename PositionA, typename RadiusA, typename PositionB>
[[nodiscard]] constexpr bool
Overlap(Circle<PositionA, RadiusA> a, Vec2<PositionB> b) noexcept
{
  const auto d = b - a.p;
  return Dot(d, d) <= a.r * a.r;
}

template<typename Position0, typename Position1, typename Radius1>
[[nodiscard]] constexpr bool
Overlap(Vec2<Position0> p0, Circle<Position1, Radius1> c1) noexcept
{
  const auto d = p0 - c1.p;
  return Dot(d, d) <= c1.r * c1.r;
}

}
