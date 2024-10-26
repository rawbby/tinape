#pragma once

#include <geometry/aabb.h>
#include <geometry/circle.h>
#include <index/index.h>

#include <platform.h>

#include <random>
#include <span>

class MyScene
{
protected:
  using dist_t = std::uniform_real_distribution<float>;

  std::random_device rd;
  std::mt19937 mt;

  std::vector<Dynamic> circles{};
  std::vector<SDL_Color> colors{};

public:
  MyScene()
    : rd()
    , mt(rd())
  {
  }

  bool Init(Index n)
  {
    FillRandomCircles(n);
    return true;
  }

  ~MyScene() = default;

  std::span<Dynamic> GetCircles()
  {
    return circles;
  }

  Dynamic& GetCircle(Index index)
  {
    return circles[index];
  }

  std::span<SDL_Color> GetColors()
  {
    return colors;
  }

  SDL_Color& GetColor(Index index)
  {
    return colors[index];
  }

public:
  bool RandomBool()
  {
    return std::uniform_int_distribution(-1, 1)(mt);
  }

  Vec2F RandomPoint()
  {
    const auto puffer = static_cast<float>(c_5 * constraint::max_extend);
    const auto x = dist_t(puffer, constraint::world_width - puffer)(mt);
    const auto y = dist_t(puffer, constraint::world_height - puffer)(mt);
    return { x, y };
  }

  Vec2F RandomVelocity()
  {
    const auto a = dist_t(0.0f, 2.0f * std::numbers::pi_v<float>)(mt);
    const auto v = dist_t(0.0f, static_cast<float>(constraint::max_velocity))(mt);
    return { std::cos(a) * v, std::sin(a) * v };
  }

  Float RandomRadius()
  {
    return dist_t(static_cast<float>(constraint::min_extend), static_cast<float>(constraint::max_extend))(mt);
  }

  SDL_Color RandomColor()
  {
    auto dist_c = std::uniform_int_distribution<int>(128, 255);
    auto dist_f = std::uniform_int_distribution<int>(0, 4)(mt);
    return { static_cast<std::uint8_t>(dist_c(mt) - (dist_f == 1 ? c0 : c128)),
             static_cast<std::uint8_t>(dist_c(mt) - (dist_f == 2 ? c0 : c128)),
             static_cast<std::uint8_t>(dist_c(mt) - (dist_f == 3 ? c0 : c128)),
             255 };
  }

  void FillRandomCircles(Index n)
  {
    circles.reserve(n);
    colors.reserve(n);

    for (unsigned i = 0; i < n; ++i) {
      while (true) {
        auto c = Circle{ RandomPoint(), RandomRadius() };

        bool overlap = false;
        for (const auto o : circles) {
          if (Overlap(c, Circle{ o.p, o.r })) {
            overlap = true;
            break;
          }
        }

        if (!overlap) {
          circles.emplace_back(c.p, c.r, RandomVelocity());
          colors.push_back(RandomColor());
          break;
        }
      }
    }
  }
};
