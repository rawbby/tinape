#pragma once

#include "../base.h"

namespace base {

/** Axis Aligned Bounding Box. Cheap to calculate upper bound for broad phase. */
template<typename MinX, typename MinY, typename MaxX, typename MaxY>
struct AABB
{
  Vec2<MinX, MinY> min;
  Vec2<MinX, MinY> max;

  constexpr inline AABB(MinX min_x, MinY min_y, MaxX max_x, MaxY max_y) noexcept
    : min(min_x, min_y)
    , max(max_x, max_y)
  {
  }
};

/**
 * Axis Aligned Bounding Box in a 45 Degree Rotated (and Scaled) Universe.
 * Surprisingly Cheap to calculate. Enhances the AABB broad phase check.
 */
template<typename MinX, typename MinY, typename MaxX, typename MaxY>
struct R45BB
{
  Vec2<MinX, MinY> min;
  Vec2<MaxX, MaxY> max;

  constexpr inline R45BB(MinX min_x, MinY min_y, MaxX max_x, MaxY max_y) noexcept
    : min(min_x, min_y)
    , max(max_x, max_y)
  {
  }
};

// clang-format off
template<typename AMinX, typename AMinY, typename AMaxX, typename AMaxY,
         typename BMinX, typename BMinY, typename BMaxX, typename BMaxY>
constexpr inline bool
MayOverlap(AABB<AMinX, AMinY, AMaxX, AMaxY> a, AABB<BMinX, BMinY, BMaxX, BMaxY> b) noexcept
{
return (a.min.x < b.max.x && a.max.x > b.min.x) &&  // Overlap on the X axis
       (a.min.y < b.max.y && a.max.y > b.min.y);    // Overlap on the Y axis
}
// clang-format on

// clang-format off
template<typename AMinX, typename AMinY, typename AMaxX, typename AMaxY,
         typename BMinX, typename BMinY, typename BMaxX, typename BMaxY>
constexpr inline bool
MayOverlap(R45BB<AMinX, AMinY, AMaxX, AMaxY> a, R45BB<BMinX, BMinY, BMaxX, BMaxY> b) noexcept
{
return (a.min.x < b.max.x && a.max.x > b.min.x) &&  // Overlap on the X axis
       (a.min.y < b.max.y && a.max.y > b.min.y);    // Overlap on the Y axis
}
// clang-format on

}
