#pragma once

#include "./circle.h"

#include "../base.h"

#include <cnl/all.h>

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

    auto s = std::max(cnl::abs(e.x), cnl::abs(e.y)) / MaxLength; // #subdivisions
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
};

namespace internal {

constexpr auto
Clamp01(auto value)
{
  if (value < base::c0) {
    return decltype(value){ base::c0 };
  }
  if (value > base::c1) {
    return decltype(value){ base::c1 };
  }
  return value;
}

}

template<typename Position0, typename Extend0, typename Position1, typename Radius1>
constexpr bool
Overlap(LineSegment<Position0, Extend0> l, Circle<Position1, Radius1> c) noexcept
{
  const auto ee = Dot(l.e, l.e);
  if (ee == 0.0) {
    return Overlap(c, l.p);
  }

  const auto t = Dot(c.p - l.p, l.e) / ee;
  const auto a = l.p + internal::Clamp01(t) * l.e;

  return Overlap(c, a);
}

}
