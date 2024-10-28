#include <geometry.h>

int
main()
{
  using namespace base;

  constexpr auto a = Circle<float, float>{ { 1.0f, 1.0f }, 1.4f };
  constexpr auto b = Circle<float, float>{ { 3.0f, 3.0f }, 1.4f };
  constexpr auto c = a;

  static_assert(!Overlap(a, b));
  static_assert(Overlap(a, c));

  static_assert(MayOverlap(a.AABB(), b.AABB()));
  static_assert(!MayOverlap(a.R45BB(), b.R45BB()));

  constexpr auto d = DynamicCircle<float, float, float>{ { 1.5f, 0.5f }, .5f, { 1.0f, 1.0f } };
  constexpr auto e = DynamicCircle<float, float, float>{ { 0.5f, 1.5f }, .5f, { 1.0f, 1.0f } };
  constexpr auto f = d;

  static_assert(!Overlap(d, e));
  static_assert(Overlap(d, f));

  static_assert(MayOverlap(d.AABB(), e.AABB()));
  static_assert(!MayOverlap(d.R45BB(), e.R45BB()));
}
