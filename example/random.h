#pragma once

#include <accelerator/constraint.h>
#include <geometry/circle.h>
#include <index/index.h>

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
  static inline dist_t dist(float min, float max) noexcept
  {
    constexpr float lo = -std::numeric_limits<float>::max();
    return dist_t{ std::nextafterf(min, lo), max };
  }

public:
  Vec2F random_point()
  {
    const auto puffer = static_cast<float>(c_5 * constraint::max_extend);
    const auto x = dist(puffer, constraint::world_width - puffer)(mt);
    const auto y = dist(puffer, constraint::world_height - puffer)(mt);
    return { x, y };
  }

  Vec2F random_velocity()
  {
    const auto a = dist(0.0f, 2.0f * std::numbers::pi_v<float>)(mt);
    const auto v = dist(0.25f, static_cast<float>(constraint::max_velocity / 8.0f))(mt);
    return { std::cos(a) * v, std::sin(a) * v };
  }

  Float random_radius()
  {
    return dist(static_cast<float>(0.55f * constraint::min_extend), static_cast<float>(0.45f * constraint::max_extend))(mt);
  }

  glm::ivec3 random_color()
  {
    auto dist_c = std::uniform_int_distribution<int>(128, 255);
    auto dist_f = std::uniform_int_distribution<int>(0, 4)(mt);
    return {
      dist_c(mt) - (dist_f == 1 ? c0 : c128),
      dist_c(mt) - (dist_f == 2 ? c0 : c128),
      dist_c(mt) - (dist_f == 3 ? c0 : c128),
    };
  }

  void fill_random_circles(std::vector<Dynamic>& circles, Index n)
  {

    circles.reserve(n);

    for (unsigned i = 0; i < n; ++i) {
      while (true) {
        auto c = Circle{ random_point(), random_radius() };

        bool overlap = false;
        for (const auto o : circles) {
          if (Overlap(c, Circle{ o.p, o.r })) {
            overlap = true;
            break;
          }
        }

        if (!overlap) {
          circles.emplace_back(c.p, c.r, random_velocity());
          break;
        }
      }
    }
  }

  void update_random_circles(std::vector<Dynamic>& circles)
  {
    const auto n = circles.size();

    for (std::size_t i = 0; i < n; ++i) {
      circles[i].v = random_velocity();

      if (circles[i].p.x < c0)
        circles[i].v.x = c1;
      if (circles[i].p.x > constraint::world_width)
        circles[i].v.x = -c1;
      if (circles[i].p.y < c0)
        circles[i].v.y = c1;
      if (circles[i].p.y > constraint::world_height)
        circles[i].v.y = -c1;
    }
  }
};
