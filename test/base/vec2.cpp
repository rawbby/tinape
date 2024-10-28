#include <base.h>

int
main()
{
  using namespace base;

  constexpr auto a = Vec2<Index>{ 1, 0 };
  constexpr auto b = Vec2<Index>{ 0, 1 };
  static_assert(a + b == Vec2<Index>{ 1, 1 });
}
