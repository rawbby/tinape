#pragma once

#include "index.h"
#include "limit.h"

#include <cmath>
#include <numbers>
#include <random>
#include <vector>

#include <glm/glm.hpp>

using f32 = glm::lowp_f32;
using vec2 = glm::lowp_vec2;

struct Circle
{
  vec2 p;
  f32 r;

  [[nodiscard]] bool overlap(Circle c) const
  {
    auto diff = p - c.p;
    auto radi = r + c.r;

    auto xs = diff.x * diff.x;
    auto ys = diff.y * diff.y;
    auto rs = radi * radi;

    return xs + ys <= rs;
  }
};

struct DynamicCircle : public Circle
{
  glm::lowp_vec2 v;

  DynamicCircle(vec2 p, f32 r, vec2 v)
    : Circle(p, r)
    , v(v)
  {
  }

  DynamicCircle(Circle c, vec2 v)
    : Circle(c)
    , v(v)
  {
  }

  DynamicCircle(Circle c)
    : Circle(c)
    , v(0.0f, 0.0f)
  {
  }

  [[nodiscard]] Circle hull() const
  {
    auto vh = 0.5f * v;
    return { p + vh, r + glm::length(vh) };
  }

  [[nodiscard]] Circle advance(float dt) const
  {
    return { p + dt * v, r };
  }

  [[nodiscard]] Circle advanced() const
  {
    return { p + v, r };
  }
};

void
fill_random_circles(std::vector<DynamicCircle>& circles, Index n)
{
  using namespace std;
  using dist_t = uniform_real_distribution<float>;
  constexpr unsigned max_width = 1024u;
  constexpr unsigned max_height = 1024u;
  constexpr float lo = numeric_limits<float>::min();

  dist_t dist_x(nextafterf(0.5 * limit::max_extend, lo), max_width - 0.5 * limit::max_extend);
  dist_t dist_y(nextafterf(0.5 * limit::max_extend, lo), max_height - 0.5 * limit::max_extend);
  dist_t dist_r(nextafterf(0.5f, lo), 0.5 * limit::max_extend);
  dist_t dist_a(nextafterf(0.0f, lo), 2.0f * std::numbers::pi_v<float>);
  dist_t dist_v(nextafterf(0.0f, lo), limit::max_velocity);

  random_device rd;
  mt19937 mt(rd());

  for (unsigned i = 0; i < n; ++i) {
    float a = dist_a(mt);
    float v = dist_v(mt);
    float vx = v * std::cos(a);
    float vy = v * std::sin(a);
    circles.emplace_back(vec2{ dist_x(mt), dist_y(mt) }, dist_r(mt), vec2{ vx, vy });
  }
}
