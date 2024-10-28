#pragma once

#include <collision.h>
#include <platform.h>

#include <random>
#include <span>

class MyScene
{
protected:
  using dist_t = std::uniform_real_distribution<float>;

  std::random_device rd;
  std::mt19937 mt;

  std::vector<DynamicCircle> circles{};
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

  std::span<DynamicCircle> GetCircles()
  {
    return circles;
  }

  DynamicCircle& GetCircle(Index index)
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

  Vec2<Position> RandomPoint()
  {
    const auto r = static_cast<float>(0.5f * max_extend_f);
    const auto x = dist_t(r, world_width - r)(mt);
    const auto y = dist_t(r, world_height - r)(mt);
    return { x, y };
  }

  Vec2<Velocity> RandomVelocity()
  {
    const auto a = dist_t(0.0f, 2.0f * std::numbers::pi_v<float>)(mt);
    const auto v = dist_t(0.0f, max_velocity_f)(mt);
    return { std::cos(a) * v, std::sin(a) * v };
  }

  Radius RandomRadius()
  {
    return dist_t(0.5f * min_extend_f, 0.5f * max_extend_f)(mt);
  }

  SDL_Color RandomColor()
  {
    auto dist_c = std::uniform_int_distribution<std::uint8_t>(127, 255);
    auto dist_f = std::uniform_int_distribution<std::uint8_t>(0, 3)(mt);

    auto r = dist_c(mt);
    auto g = dist_c(mt);
    auto b = dist_c(mt);

    switch (dist_f) {
      case 1:
        r -= 127;
      case 2:
        g -= 127;
      default:
        b -= 127;
    }

    return { r, g, b, 255 };
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
