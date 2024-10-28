#include <geometry.h>

#include <iostream>

int
main()
{
  using namespace base;

  {
    constexpr auto a = Circle<float, float>{ { 1.0f, 1.0f }, 1.4f };
    constexpr auto b = Circle<float, float>{ { 3.0f, 3.0f }, 1.4f };
    constexpr auto c = a;

    static_assert(!Overlap(a, b));
    static_assert(Overlap(a, c));

    static_assert(MayOverlap(a.AABB(), b.AABB()));
    static_assert(!MayOverlap(a.R45BB(), b.R45BB()));
  }

  {
    constexpr auto d = DynamicCircle<float, float, float>{ { 1.5f, 0.5f }, .5f, { 1.0f, 1.0f } };
    constexpr auto e = DynamicCircle<float, float, float>{ { 0.5f, 1.5f }, .5f, { 1.0f, 1.0f } };
    constexpr auto f = d;

    static_assert(!Overlap(d, e));
    static_assert(Overlap(d, f));

    static_assert(MayOverlap(d.AABB(), e.AABB()));
    static_assert(!MayOverlap(d.R45BB(), e.R45BB()));
  }

  {
    constexpr auto l = LineSegment<float, float>{ { 1.0f, 1.0f }, { 3.0f, 3.0f } };
    constexpr auto ca = Circle<float, float>{ { 0.0f, 0.0f }, static_cast<float>(sqrt2ub) };
    constexpr auto cb = Circle<float, float>{ { 1.0f, 2.0f }, 1.0f };

    static_assert(Overlap(ca, Vec2<float>{ 0.0f, static_cast<float>(sqrt2ub) }));
    static_assert(Overlap(ca, Vec2<float>{ static_cast<float>(sqrt2ub), 0.0f }));
    static_assert(!Overlap(ca, Vec2<float>{ 0.0f, 1.51f }));
    static_assert(!Overlap(ca, Vec2<float>{ 1.51f, 0.0f }));

    static_assert(Overlap(l, ca));
    static_assert(Overlap(l, cb));
  }

  {
    LineSegment<float, float> l{ { 0.0f, 0.0f }, { 101.0f, 101.0f } };
    std::vector<LineSegment<float, float>> segments{};

    l.Subdivide<float, 10>(segments);

    std::cout << "original: {(" << l.p.x << ", " << l.p.y << "), (" << l.e.x << ", " << l.e.y << ")}\n";
    if (segments.size() != 11)
      std::exit(1);

    const auto last = segments.back();
    if (last.p + last.e != Vec2<float>{ 101.0f, 101.0f })
      std::exit(1);

    for (auto segment : segments)
      std::cout << "{(" << segment.p.x << ", " << segment.p.y << "), (" << segment.e.x << ", " << segment.e.y << ")}\n";
  }
}
