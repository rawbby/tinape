#pragma once

#include "./aabb.hpp"
#include "./vec2.hpp"

// clang-format off
namespace internal{enum class IsCircleHelper_{};}
// clang-format on

template<typename T>
concept IsCircle = std::is_same_v<typename T::TypeId, internal::IsCircleHelper_>;

template<typename P, typename R>
struct Circle
{
  using TypeId = internal::IsCircleHelper_;
  using Position = P;
  using Radius = R;

  Vec2<Position> p;
  Radius r;

  [[nodiscard]] constexpr auto aabb() const noexcept
  {
    return AABB{ p.x - r, p.y - r, p.x + r, p.y + r };
  }

  [[nodiscard]] constexpr auto r45bb(auto sqrt2ub) const noexcept
  {
    const auto x_ = p.x - p.y;
    const auto y_ = p.x + p.y;
    const auto r_ = r * sqrt2ub;

    const auto min_x = x_ - r_;
    const auto min_y = y_ - r_;
    const auto max_x = x_ + r_;
    const auto max_y = y_ + r_;
    return R45BB{ min_x, min_y, max_x, max_y };
  }
};

[[nodiscard]] constexpr bool
Overlap(IsCircle auto a, IsCircle auto b) noexcept
{
  const auto x = b.r + a.r;
  const auto d = b.p - a.p;
  return Dot(d, d) <= x * x;
}

[[nodiscard]] constexpr bool
Overlap(IsCircle auto a, IsVec2 auto b) noexcept
{
  const auto d = b - a.p;
  return Dot(d, d) <= a.r * a.r;
}

[[nodiscard]] constexpr bool
Overlap(IsVec2 auto p0, IsCircle auto c1) noexcept
{
  const auto d = p0 - c1.p;
  return Dot(d, d) <= c1.r * c1.r;
}
