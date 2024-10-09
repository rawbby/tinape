#pragma once

#include "circle.h"
#include "index.h"
#include "limit.h"

#include <numbers>
#include <random>
#include <vector>

#include <glm/glm.hpp>

class Random
{
private:
  using dist_t = std::uniform_real_distribution<float>;
  std::random_device rd;
  std::mt19937 mt;

public:
  Random()
    : rd()
    , mt(rd())
  {
  }

private:
  inline dist_t dist(float min, float max) noexcept
  {
    constexpr float lo = -std::numeric_limits<float>::max();
    return dist_t{ std::nextafterf(min, lo), max };
  }

public:
  void fill_random_circles(std::vector<Dynamic>& circles, Index n)
  {
    constexpr unsigned max_width = 1024u;
    constexpr unsigned max_height = 1024u;

    auto dist_x = dist(0.5 * limit::max_extend, max_width - 0.5 * limit::max_extend);
    auto dist_y = dist(0.5 * limit::max_extend, max_height - 0.5 * limit::max_extend);
    auto dist_r = dist(0.5f, 0.5 * limit::max_extend);
    auto dist_a = dist(0.0f, 2.0f * std::numbers::pi_v<float>);
    auto dist_v = dist(0.0f, limit::max_velocity);

    for (unsigned i = 0; i < n; ++i) {
      const auto p = Vec{ dist_x(mt), dist_y(mt) };
      const auto r = dist_r(mt);
      const auto a = dist_a(mt);
      const auto v = Vec{ std::cos(a), std::sin(a) } * dist_v(mt);
      circles.emplace_back(p, r, v);
    }
  }
};
