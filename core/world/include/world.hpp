#pragma once

#include <geometry.hpp>
#include <numeric.hpp>

constexpr auto world_precision = -5; // 3.125 cm

// -8192m to 8192m (negative means invalid)
// -> 13 bits + abs(world_precision) [+sign]
// total: 19 bits
using WorldPositionUnit = Fixed<VAR, 13 - world_precision, world_precision>;
using WorldPosition = Vec2<WorldPositionUnit>;

static_assert(WorldPositionUnit::bits_ == 18);
static_assert(WorldPositionUnit::sign_ == VAR);
static_assert(std::is_same_v<WorldPositionUnit::Repr_, i32>);

constexpr auto world_min_extend = as_fixed_v<1.0>;
constexpr auto world_max_extend = as_fixed_v<4.0>;
constexpr auto world_chunk_extend = as_fixed_v<8.0>;
constexpr auto world_bounds = AABB{
  as_fixed_v<0.0>,
  as_fixed_v<0.0>,
  as_fixed_v<1024.0>,
  as_fixed_v<1024.0>
};

// can not intersect more than two chunks along one axis
// meaning max move is chunk_extend - max_extend = 4m.
// -> 2 bits + abs(world_precision) [+sign]
// total: 8 bits
using WorldVelocityUnit = Fixed<VAR, 2 - world_precision, world_precision>;
using WorldVelocity = Vec2<WorldVelocityUnit>;

static_assert(WorldVelocityUnit::bits_ == 7);
static_assert(WorldVelocityUnit::sign_ == VAR);
static_assert(std::is_same_v<WorldVelocityUnit::Repr_, i8>);

// datatype for storing extend data like diameter, width, height ...
// max_extend = 4m.
// -> 2 bits + abs(world_precision) [+sign]
// total: 8 bits
using WorldExtendUnit = Fixed<VAR, 2 - world_precision, world_precision>;

static_assert(WorldExtendUnit::bits_ == 7);
static_assert(WorldExtendUnit::sign_ == VAR);
static_assert(std::is_same_v<WorldExtendUnit::Repr_, i8>);

using WorldCircle = Circle<WorldPositionUnit, WorldExtendUnit>;
using WorldDynamicCircle = DynamicCircle<WorldPositionUnit, WorldExtendUnit, WorldVelocityUnit>;
using WorldLineSegment = LineSegment<WorldPositionUnit, WorldExtendUnit>;

class World
{
  std::vector<WorldCircle> circles_;
  std::vector<WorldDynamicCircle> dynamic_circles_;
  std::vector<WorldLineSegment> line_segments_;

public:
  Index push_back(IsCircle auto circle)
  {
    circles_.emplace_back(circle.p, circle.r);
    return circles_.size() - 1;
  }

  Index push_back(IsDynamicCircle auto circle)
  {
    dynamic_circles_.emplace_back(circle.p, circle.r, circle.v);
    return dynamic_circles_.size() - 1;
  }

  IndexPair push_back(IsLineSegment auto line)
  {
    static_assert(std::is_same_v<typename decltype(line)::Position, WorldPositionUnit>);
    Index beg = line_segments_.size();
    line.Subdivide<WorldExtendUnit, 4>(line_segments_);
    Index end = line_segments_.size();
    return { beg, end };
  }
};
