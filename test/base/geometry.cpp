#include "base/fixed.h"
#include "base/vec2.h"
#include "geometry/aabb.h"
#include "geometry/circle.h"
#include "geometry/dynamic_circle.h"
#include "geometry/line_segment.h"
#include <cstdlib>

#include <iostream>
#include <vector>

int
main()
{
  using namespace base;

  {
    constexpr auto a = Circle<float, float>{ .p = { 1.0F, 1.0F }, .r = 1.4F };
    constexpr auto b = Circle<float, float>{ .p = { 3.0F, 3.0F }, .r = 1.4F };
    constexpr auto c = a;

    static_assert(!Overlap(a, b));
    static_assert(Overlap(a, c));

    static_assert(MayOverlap(a.AABB(), b.AABB()));
    static_assert(!MayOverlap(a.R45BB(), b.R45BB()));
  }

  {
    constexpr auto d = DynamicCircle<float, float, float>{ .p = { 1.5F, 0.5F }, .r = .5f, .v = { 1.0F, 1.0F } };
    constexpr auto e = DynamicCircle<float, float, float>{ .p = { 0.5F, 1.5F }, .r = .5f, .v = { 1.0F, 1.0F } };
    constexpr auto f = d;

    static_assert(!Overlap(d, e));
    static_assert(Overlap(d, f));

    static_assert(MayOverlap(d.AABB(), e.AABB()));
    static_assert(!MayOverlap(d.R45BB(), e.R45BB()));
  }

  {
    constexpr auto l = LineSegment<float, float>{ .p = { 1.0F, 1.0F }, .e = { 3.0F, 3.0F } };
    constexpr auto ca = Circle<float, float>{ .p = { 0.0F, 0.0F }, .r = static_cast<float>(sqrt2ub) };
    constexpr auto cb = Circle<float, float>{ .p = { 1.0F, 2.0F }, .r = 1.0F };

    static_assert(Overlap(ca, Vec2<float>{ 0.0F, static_cast<float>(sqrt2ub) }));
    static_assert(Overlap(ca, Vec2<float>{ static_cast<float>(sqrt2ub), 0.0F }));
    static_assert(!Overlap(ca, Vec2<float>{ 0.0F, 1.51F }));
    static_assert(!Overlap(ca, Vec2<float>{ 1.51F, 0.0F }));

    static_assert(Overlap(l, ca));
    static_assert(Overlap(l, cb));
  }

  {
    LineSegment<float, float> const l{ .p = { 0.0F, 0.0F }, .e = { 101.0F, 101.0F } };
    std::vector<LineSegment<float, float>> segments{};

    l.Subdivide<float, 10>(segments);

    std::cout << "original: {(" << l.p.x << ", " << l.p.y << "), (" << l.e.x << ", " << l.e.y << ")}\n";
    if (segments.size() != 11) {
      std::exit(1);
    }

    const auto last = segments.back();
    if (last.p + last.e != Vec2<float>{ 101.0F, 101.0F }) {
      std::exit(1);
    }

    for (auto segment : segments) {
      std::cout << "{(" << segment.p.x << ", " << segment.p.y << "), (" << segment.e.x << ", " << segment.e.y << ")}\n";
    }
  }
}
