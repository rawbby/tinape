#pragma once

#include "../base.h"

#include "./aabb.h"

namespace base {

template<typename Position, typename Radius>
struct Circle
{
  Vec2<Position> p;
  Radius r;

  constexpr inline auto AABB() const noexcept
  {
    const auto min_x = p.x - r;
    const auto min_y = p.y - r;
    const auto max_x = p.x + r;
    const auto max_y = p.y + r;
    return base::AABB{ min_x, min_y, max_x, max_y };
  }

  constexpr inline auto R45BB() const noexcept
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
[[nodiscard]] constexpr inline bool
Overlap(Circle<PositionA, RadiusA> a, Circle<PositionB, RadiusB> b) noexcept
{
  const auto x = b.r + a.r;
  const auto dp = b.p - a.p;
  return Dot(dp, dp) <= x * x;
}

}
