#pragma once

#include "./circle.h"

#include "../base.h"

namespace base {

template<typename Position, typename Extend>
struct LineSegment
{
  Vec2<Position> p;
  Vec2<Extend> e;

  template<typename Extend_, int MaxLength>
  void Subdivide(std::vector<LineSegment<Position, Extend_>>& container) const
  {
    static_assert(MaxLength <= std::numeric_limits<Extend_>::max());

    auto s = std::max(abs(e.x), abs(e.y)) / MaxLength; // #subdivisions
    auto i = static_cast<unsigned>(s);
    if (i < s) {
      ++i;
    }

    const Vec2<Position> end = p + e;

    auto last = container.emplace_back(p, (end - p) / i);
    while (--i) {
      const Vec2<Position> p_{ last.p + last.e };
      last = container.emplace_back(p_, (end - p_) / i);
    }
  }

  [[nodiscard]] Vec2<Position> Min() const
  {
    return { Min(p.x, p.x + e.x), Min(p.y, p.y + e.y) };
  }
};

namespace internal {

constexpr auto
Clamp01(auto value)
{
  if (value < 0) {
    return decltype(value){ 0 };
  }
  if (value > 1) {
    return decltype(value){ 1 };
  }
  return value;
}

}

template<typename Position0, typename Extend0, typename Position1, typename Radius1>
constexpr bool
Overlap(LineSegment<Position0, Extend0> l, Circle<Position1, Radius1> c) noexcept
{
  const auto ee = Dot(l.e, l.e);
  if (ee == 0) {
    return Overlap(c, l.p);
  }

  const auto t = Dot(c.p - l.p, l.e) / ee;
  const auto a = l.p + internal::Clamp01(t) * l.e;

  return Overlap(c, a);
}

}
