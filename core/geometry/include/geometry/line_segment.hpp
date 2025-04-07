#pragma once

#include "./circle.hpp"
#include "./vec2.hpp"

#include <vector>

// clang-format off
namespace internal{enum class IsLineSegmentHelper_{};}
// clang-format on

template<typename T>
concept IsLineSegment = std::is_same_v<typename T::TypeId, internal::IsLineSegmentHelper_>;

template<typename P, typename E>
struct LineSegment
{
  using TypeId = internal::IsLineSegmentHelper_;
  using Position = P;
  using Extend = E;

  Vec2<Position> p;
  Vec2<Extend> e;

  template<typename Position_, typename Extend_, int MaxLength>
  void Subdivide(std::vector<LineSegment<Position_, Extend_>>& container) const
  {
    static_assert(MaxLength <= Extend_::max());

    auto s = std::max(std::abs(e.x), std::abs(e.y)) / MaxLength; // #subdivisions
    auto i = static_cast<unsigned>(s);
    if (i < s)
      ++i;

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
  if (value < 0)
    return decltype(value){ 0 };
  if (value > 1)
    return decltype(value){ 1 };
  return value;
}
}

constexpr bool
Overlap(IsLineSegment auto l, IsCircle auto c) noexcept
{
  const auto ee = Dot(l.e, l.e);
  if (ee == 0)
    return Overlap(c, l.p);

  const auto t = Dot(c.p - l.p, l.e) / ee;
  const auto a = l.p + internal::Clamp01(t) * l.e;

  return Overlap(c, a);
}
