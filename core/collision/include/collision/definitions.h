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

constexpr auto max_extend = 12u;
constexpr auto min_extend = 4u;
constexpr auto max_velocity = 4u;
constexpr auto max_aabb_extend = 16u;

constexpr auto max_extend_f = 12.0f;
constexpr auto min_extend_f = 4.0f;
constexpr auto max_velocity_f = 4.0f;
constexpr auto max_aabb_extend_f = 16.0f;

constexpr auto world_width = 512u;
constexpr auto world_height = 256u;

constexpr auto world_width_f = 512.0f;
constexpr auto world_height_f = 256.0f;

using Position = base::Fixed<1, 13, 10>;
using Radius = base::Fixed<0, 3, 13>;
using Velocity = base::Fixed<1, 2, 13>;

using Circle = base::Circle<Position, Radius>;
using DynamicCircle = base::DynamicCircle<Position, Radius, Velocity>;

using base::Advance;
using base::Overlap;

template<typename MinX, typename MinY, typename MaxX, typename MaxY>
using AABB = base::AABB<MinX, MinY, MaxX, MaxY>;

template<typename MinX, typename MinY, typename MaxX, typename MaxY>
using R45BB = base::R45BB<MinX, MinY, MaxX, MaxY>;

using base::MayOverlap;

constexpr auto max_world_width = static_cast<unsigned>(static_cast<Index>(~0u) / max_aabb_extend);
constexpr auto max_world_height = static_cast<unsigned>(static_cast<Index>(~0u) / max_aabb_extend);

constexpr auto max_world_width_f = static_cast<float>(max_world_width);
constexpr auto max_world_height_f = static_cast<float>(max_world_height);

// constexpr auto world_width = 4096u;
// constexpr auto world_height = 2048u;

// constexpr auto world_width_f = 4096.0f;
// constexpr auto world_height_f = 2048.0f;

constexpr inline Index
Quantify(auto scalar) noexcept
{
  static_assert(world_width <= max_world_width);
  static_assert(world_height <= max_world_height);

  auto index = cnl::floor(scalar);
  index >>= std::countr_zero(max_aabb_extend);
  return static_cast<Index>(index);
}

constexpr inline IndexPair
Quantify(auto a, auto b) noexcept
{
  return { Quantify(a), Quantify(b) };
}

template<typename S>
constexpr inline IndexPair
Quantify(Vec2<S> s) noexcept
{
  return { Quantify(s.x), Quantify(s.y) };
}
