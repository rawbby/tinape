#pragma once

#include <bit>
#include <glm/glm.hpp>

using F32 = glm::lowp_float32;
using Vec = glm::lowp_vec2;

[[maybe_unused]] constexpr inline F32
InverseSqrt(F32 val) noexcept
{
  const auto y = std::bit_cast<F32>(0x5f3759df - (std::bit_cast<unsigned int>(val) >> 1));
  return y * (1.5f - (val * 0.5f * y * y));
}

[[maybe_unused]] constexpr inline Vec
Rot90(Vec a) noexcept
{
  return { -a.y, a.x };
}

[[maybe_unused]] constexpr inline Vec
Rot180(Vec a) noexcept
{
  return { -a.x, -a.y };
}

[[maybe_unused]] constexpr inline Vec
Rot270(Vec a) noexcept
{
  return { a.y, -a.x };
}

[[maybe_unused]] constexpr inline F32
Dot(Vec a, Vec b) noexcept
{
  return (a.x * b.x) + (a.y * b.y);
}

[[maybe_unused]] constexpr inline F32
F32Projection(Vec a, Vec b) noexcept
{
  return Dot(a, b) * InverseSqrt(Dot(b, b));
}

[[maybe_unused]] constexpr inline Vec
VecProjection(Vec a, Vec b) noexcept
{
  return (Dot(a, b) / Dot(b, b)) * b;
}

[[maybe_unused]] constexpr inline F32
F32Rejection(Vec a, Vec b) noexcept
{
  return F32Projection(a, Rot90(b));
}

[[maybe_unused]] constexpr inline Vec
VecRejection(Vec a, Vec b) noexcept
{
  return VecProjection(a, Rot90(b));
}
