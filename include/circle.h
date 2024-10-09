#pragma once

#include "./math.h"

struct Circle
{
  Vec p;
  F32 r;
};

struct Line
{
  Vec p;
  Vec v;
};

constexpr inline bool
overlap(Circle a, Circle b) noexcept
{
  const auto d = b.p - a.p;
  const auto rr = b.r + a.r;
  return (d.x * d.x) + (d.y * d.y) < (rr * rr);
}

constexpr inline bool
overlap(Line line, Circle circle) noexcept
{
  return F32Rejection(circle.p - line.p, line.v) < circle.r;
}

constexpr inline bool
overlap(Line line, Circle circle, Vec& contact) noexcept
{
  const auto a = circle.p - line.p;
  const auto b = line.v;

  const auto area2 = a.y * b.x - a.x * b.y;
  const auto b_inv = InverseSqrt((b.x * b.x) + (b.y * b.y));

  const auto h = area2 * b_inv;
  const auto o = h < circle.r;

  if (o) {
    const auto b_norm = b * b_inv;
    const auto a1 = (a * b_norm) * b_norm;
    contact = line.p + a1;
  }

  return o;
}

struct Dynamic
{
  Vec p;
  F32 r;
  Vec v;
};

constexpr inline Circle
advance(Dynamic dynamic) noexcept
{
  return { dynamic.p + dynamic.v, dynamic.r };
}

constexpr inline Circle
advance(Dynamic dynamic, float dt) noexcept
{
  return { dynamic.p + dt * dynamic.v, dynamic.r };
}

struct AABB
{
  Vec min;
  Vec max;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "google-explicit-constructor"

  [[maybe_unused]] constexpr inline AABB(Circle c) noexcept
    : min(c.p - c.r)
    , max(c.p + c.r)
  {
  }

  [[maybe_unused]] constexpr inline AABB(Dynamic d) noexcept
    : min(d.p - d.r)
    , max(d.p + d.r)
  {
    // clang-format off
    if (d.v.x > 0.0f) max.x += d.v.x;
    else              min.x += d.v.x;
    if (d.v.y > 0.0f) max.y += d.v.y;
    else              min.y += d.v.y;
    // clang-format on
  }

  [[maybe_unused]] constexpr inline AABB(Line l) noexcept
    : min(l.p)
    , max(l.p)
  {
    // clang-format off
    if (l.v.x > 0.0f) max.x += l.v.x;
    else              min.x += l.v.x;
    if (l.v.y > 0.0f) max.y += l.v.y;
    else              min.y += l.v.y;
    // clang-format on
  }

#pragma clang diagnostic pop
};

constexpr inline bool
may_overlap(AABB a, AABB b) noexcept
{
  const auto s1 = a.max.x <= b.min.x;
  const auto s2 = b.max.x <= a.min.x;
  const auto s3 = a.max.y <= b.min.y;
  const auto s4 = b.max.y <= a.min.y;
  return s1 | s2 | s3 | s4;
}
