#pragma once

#include <base.h>
#include <geometry.h>

using Index = base::Index;
using IndexPair = base::IndexPair;

template<typename X, typename Y = X>
using Vec2 = base::Vec2<X, Y>;

template<typename X, typename Y = X, typename Z = X>
using Vec3 = base::Vec3<X, Y, Z>;

template<typename X, typename Y = X, typename Z = X, typename W = X>
using Vec4 = base::Vec4<X, Y, Z, W>;

using base::Abs;
using base::Dot;
using base::Length;
using base::Normalize;

constexpr auto max_extend = 12U;
constexpr auto min_extend = 4U;
constexpr auto max_velocity = 4U;
constexpr auto max_aabb_extend = 16U;

constexpr auto max_extend_f = 12.0F;
constexpr auto min_extend_f = 4.0F;
constexpr auto max_velocity_f = 4.0F;
constexpr auto max_aabb_extend_f = 16.0F;

constexpr auto world_width = 512U;
constexpr auto world_height = 256U;

constexpr auto world_width_f = 512.0F;
constexpr auto world_height_f = 256.0F;

using Position = base::Fixed<1, 13, 10>; // NOLINT(*-magic-numbers)
using Radius = base::Fixed<0, 3, 13>;    // NOLINT(*-magic-numbers)
using Velocity = base::Fixed<1, 2, 13>;  // NOLINT(*-magic-numbers)
using Extend = base::Fixed<1, 5, 10>;    // NOLINT(*-magic-numbers)

using Circle = base::Circle<Position, Radius>;
using DynamicCircle = base::DynamicCircle<Position, Radius, Velocity>;
using LineSegment = base::LineSegment<Position, Extend>;

using base::Advance;
using base::Overlap;

template<typename MinX, typename MinY, typename MaxX, typename MaxY>
using AABB = base::AABB<MinX, MinY, MaxX, MaxY>;

template<typename MinX, typename MinY, typename MaxX, typename MaxY>
using R45BB = base::R45BB<MinX, MinY, MaxX, MaxY>;

using base::MayOverlap;

// constexpr auto world_width = 4095u;
// constexpr auto world_height = 2047u;

// constexpr auto world_width_f = 4095.0f;
// constexpr auto world_height_f = 2047.0f;

constexpr Index
Quantify(auto scalar) noexcept
{
  auto index = cnl::floor(scalar);
  index >>= std::countr_zero(max_aabb_extend);
  return static_cast<Index>(index);
}

constexpr IndexPair
Quantify(auto a, auto b) noexcept
{
  return { Quantify(a), Quantify(b) };
}

template<typename S>
constexpr IndexPair
Quantify(Vec2<S> s) noexcept
{
  return { Quantify(s.x), Quantify(s.y) };
}
