#include "assert.hpp"
#include "geometry.hpp"
#include "numeric.hpp"

#include <cmath>
#include <cstdlib>
#include <vector>

int
main()
{
  const auto sqrt2ub = std::nextafter(std::numbers::sqrt2_v<float>, std::numeric_limits<float>::max());

  {
    const auto a = Circle<float, float>{ .p = { 1.0F, 1.0F }, .r = 1.4F };
    const auto b = Circle<float, float>{ .p = { 3.0F, 3.0F }, .r = 1.4F };
    const auto c = a;

    ASSERT(!Overlap(a, b));
    ASSERT(Overlap(a, c));

    ASSERT(MayOverlap(a.aabb(), b.aabb()));
    ASSERT(!MayOverlap(a.r45bb(sqrt2ub), b.r45bb(sqrt2ub)));
  }

  {
    const auto d = DynamicCircle<float, float, float>{ .p = { 1.5F, 0.5F }, .r = .5f, .v = { 1.0F, 1.0F } };
    const auto e = DynamicCircle<float, float, float>{ .p = { 0.5F, 1.5F }, .r = .5f, .v = { 1.0F, 1.0F } };
    const auto f = d;

    ASSERT(!Overlap(d, e));
    ASSERT(Overlap(d, f));

    ASSERT(MayOverlap(d.aabb(), e.aabb()));
    ASSERT(!MayOverlap(d.r45bb(sqrt2ub), e.r45bb(sqrt2ub)));
  }

  {
    const auto l = LineSegment<float, float>{ .p = { 1.0F, 1.0F }, .e = { 3.0F, 3.0F } };
    const auto ca = Circle<float, float>{ .p = { 0.0F, 0.0F }, .r = static_cast<float>(sqrt2ub) };
    const auto cb = Circle<float, float>{ .p = { 1.0F, 2.0F }, .r = 1.0F };

    ASSERT(Overlap(ca, Vec2<float>{ 0.0F, static_cast<float>(sqrt2ub) }));
    ASSERT(Overlap(ca, Vec2<float>{ static_cast<float>(sqrt2ub), 0.0F }));
    ASSERT(!Overlap(ca, Vec2<float>{ 0.0F, 1.51F }));
    ASSERT(!Overlap(ca, Vec2<float>{ 1.51F, 0.0F }));

    ASSERT(Overlap(l, ca));
    ASSERT(Overlap(l, cb));
  }

  {
    LineSegment<float, float> const l{ .p = { 0.0F, 0.0F }, .e = { 101.0F, 101.0F } };
    std::vector<LineSegment<float, float>> segments{};

    l.Subdivide<float, 10>(segments);

    if (segments.size() != 11)
      std::exit(1);

    const auto [p, e] = segments.back();
    if (p + e != Vec2<float>{ 101.0F, 101.0F })
      std::exit(1);
  }
}
