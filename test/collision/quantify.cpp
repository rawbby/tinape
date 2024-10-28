#pragma once

#include <collision.h>

int
main()
{
  static_assert(Quantify(DynamicCircle{ { 16.5f, 16.5f }, 0.5f, { -0.25f, 0.25f } }.AABB().min) == IndexPair{ 0, 1 });
  static_assert(Quantify(DynamicCircle{ { 16.5f, 16.5f }, 0.5f, { 0.25f, -0.25f } }.AABB().min) == IndexPair{ 1, 0 });

  constexpr auto a = DynamicCircle{ { 0.0f, 0.0f }, 0.5f, { 0.25f, -0.25f } }.AABB().min;
  static_assert(a.x == -0.5f);
  static_assert(a.y == -0.75f);
  static_assert(Quantify(a.x) == -1);
  static_assert(Quantify(a.y) == -1);

  static_assert(Quantify(base::Fixed<1, 16, 15>{ -47.0f }) == -3);
  static_assert(Quantify(base::Fixed<1, 16, 15>{ -49.0f }) == -4);

  static_assert(DynamicCircle{ { 0.0f, 0.0f }, 0.5f, { -0.5f, -0.5f } }.AABB().min == Vec2<float>{ -1.0, -1.0 });
  static_assert(DynamicCircle{ { 0.0f, 0.0f }, 0.5f, { -0.5f, 0.5f } }.AABB().min == Vec2<float>{ -1.0, -0.5 });
  static_assert(DynamicCircle{ { 0.0f, 0.0f }, 0.5f, { 0.5f, -0.5f } }.AABB().min == Vec2<float>{ -0.5, -1.0 });
  static_assert(DynamicCircle{ { 0.0f, 0.0f }, 0.5f, { 0.5f, 0.5f } }.AABB().min == Vec2<float>{ -0.5, -0.5 });

  static_assert(Quantify(Circle{ { 16.5f, 0.5f }, 0.5f }.AABB().min) == IndexPair{ 1, 0 });
  static_assert(Quantify(Circle{ { 0.5f, 16.5f }, 0.5f }.AABB().min) == IndexPair{ 0, 1 });
}
