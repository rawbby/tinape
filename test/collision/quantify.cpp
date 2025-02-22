#pragma once

#include "collision/definitions.h"

int
main()
{
  static_assert(Quantify(DynamicCircle{ { 16.5F, 16.5F }, 0.5F, { -0.25F, 0.25F } }.AABB().min) == IndexPair{ 0, 1 });
  static_assert(Quantify(DynamicCircle{ { 16.5F, 16.5F }, 0.5F, { 0.25F, -0.25F } }.AABB().min) == IndexPair{ 1, 0 });

  constexpr auto a = DynamicCircle{ { 0.0F, 0.0F }, 0.5F, { 0.25F, -0.25F } }.AABB().min;
  static_assert(a.x == -0.5F);
  static_assert(a.y == -0.75F);
  static_assert(Quantify(a.x) == -1);
  static_assert(Quantify(a.y) == -1);

  static_assert(Quantify(base::Fixed<1, 16, 15>{ -47.0F }) == -3);
  static_assert(Quantify(base::Fixed<1, 16, 15>{ -49.0F }) == -4);

  static_assert(DynamicCircle{ { 0.0F, 0.0F }, 0.5F, { -0.5F, -0.5F } }.AABB().min == Vec2<float>{ -1.0, -1.0 });
  static_assert(DynamicCircle{ { 0.0F, 0.0F }, 0.5F, { -0.5F, 0.5F } }.AABB().min == Vec2<float>{ -1.0, -0.5 });
  static_assert(DynamicCircle{ { 0.0F, 0.0F }, 0.5F, { 0.5F, -0.5F } }.AABB().min == Vec2<float>{ -0.5, -1.0 });
  static_assert(DynamicCircle{ { 0.0F, 0.0F }, 0.5F, { 0.5F, 0.5F } }.AABB().min == Vec2<float>{ -0.5, -0.5 });

  static_assert(Quantify(Circle{ { 16.5F, 0.5F }, 0.5F }.AABB().min) == IndexPair{ 1, 0 });
  static_assert(Quantify(Circle{ { 0.5F, 16.5F }, 0.5F }.AABB().min) == IndexPair{ 0, 1 });
}
