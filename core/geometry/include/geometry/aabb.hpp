#pragma once

#include "vec2.hpp"

// clang-format off
namespace internal{enum class IsAABBHelper_{};}
namespace internal{enum class IsR45BBHelper_{};}
// clang-format on

template<typename T>
concept IsAABB = std::is_same_v<typename T::TypeId, internal::IsAABBHelper_>;

template<typename T>
concept IsR45BB = std::is_same_v<typename T::TypeId, internal::IsR45BBHelper_>;

/// Axis Aligned Bounding Box. Cheap to calculate upper bound for broad phase.
template<typename MinX, typename MinY = MinX, typename MaxX = MinX, typename MaxY = MinY>
struct AABB
{
  using TypeId = internal::IsAABBHelper_;
  using Min = Vec2<MinX, MinY>;
  using Max = Vec2<MaxX, MaxY>;

  Min min;
  Max max;

  constexpr AABB(MinX min_x, MinY min_y, MaxX max_x, MaxY max_y) noexcept
    : min(min_x, min_y)
    , max(max_x, max_y)
  {
  }
};

/// Axis Aligned Bounding Box in a 45 Degree Rotated (and Scaled) Universe.
/// Surprisingly Cheap to calculate. Enhances the AABB broad phase check.
template<typename MinX, typename MinY = MinX, typename MaxX = MinX, typename MaxY = MinY>
struct R45BB
{
  using TypeId = internal::IsR45BBHelper_;
  using Min = Vec2<MinX, MinY>;
  using Max = Vec2<MaxX, MaxY>;

  Min min;
  Max max;

  constexpr R45BB(MinX min_x, MinY min_y, MaxX max_x, MaxY max_y) noexcept
    : min(min_x, min_y)
    , max(max_x, max_y)
  {
  }
};

constexpr bool
MayOverlap(IsAABB auto lhs, IsAABB auto rhs) noexcept
{
  return (lhs.min.x < rhs.max.x && lhs.max.x > rhs.min.x) && // Overlap on the X axis
         (lhs.min.y < rhs.max.y && lhs.max.y > rhs.min.y);   // Overlap on the Y axis
}

constexpr bool
MayOverlap(IsR45BB auto lhs, IsR45BB auto rhs) noexcept
{
  return (lhs.min.x < rhs.max.x && lhs.max.x > rhs.min.x) && // Overlap on the X axis
         (lhs.min.y < rhs.max.y && lhs.max.y > rhs.min.y);   // Overlap on the Y axis
}
