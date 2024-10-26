#pragma once

#include <type/vec2.h>

#include <platform.h>

#include <accelerator/constraint.h>
#include <geometry/aabb.h>
#include <geometry/circle.h>

class MyWindow : public RendererWindow
{
protected:
  static inline Vec2<float> Transform(Vec2<float> vec)
  {
    constexpr auto factor = 3.63f / 8.0f;
    constexpr auto offset = Vec2<float>{ constraint::max_extend_f, constraint::max_extend_f };
    return factor * offset + (factor * vec);
  }

  static inline void DrawCircle(SDL_Renderer* renderer, Dynamic circle)
  {
    constexpr int n = 16;
    constexpr std::array<float, n + 1> theta{
      2.0f * std::numbers::pi_v<float> * 0.0f,    //
      2.0f * std::numbers::pi_v<float> * 0.0625f, //
      2.0f * std::numbers::pi_v<float> * 0.125f,  //
      2.0f * std::numbers::pi_v<float> * 0.1875f, //
      2.0f * std::numbers::pi_v<float> * 0.25f,   //
      2.0f * std::numbers::pi_v<float> * 0.3125f, //
      2.0f * std::numbers::pi_v<float> * 0.375f,  //
      2.0f * std::numbers::pi_v<float> * 0.4375f, //
      2.0f * std::numbers::pi_v<float> * 0.5f,    //
      2.0f * std::numbers::pi_v<float> * 0.5625f, //
      2.0f * std::numbers::pi_v<float> * 0.625f,  //
      2.0f * std::numbers::pi_v<float> * 0.6875f, //
      2.0f * std::numbers::pi_v<float> * 0.75f,   //
      2.0f * std::numbers::pi_v<float> * 0.8125f, //
      2.0f * std::numbers::pi_v<float> * 0.875f,  //
      2.0f * std::numbers::pi_v<float> * 0.9375f, //
      2.0f * std::numbers::pi_v<float> * 1.0f,    //
    };

    const auto p = Vec2<float>{ circle.p };
    const auto r = static_cast<float>(circle.r);

    for (int i = 1; i < n; ++i) {
      const auto a = Transform(p + Vec2<float>(r * std::cos(theta[i + 0]), r * std::sin(theta[i + 0])));
      const auto b = Transform(p + Vec2<float>(r * std::cos(theta[i + 1]), r * std::sin(theta[i + 1])));
      SDL_RenderLine(renderer, a.x, a.y, b.x, b.y);
    }
  }

  template<typename S>
  static inline void DrawAABB(SDL_Renderer* renderer, AABB<S> c)
  {
    const auto min = Transform(Vec2<float>{ c.min });
    const auto max = Transform(Vec2<float>{ c.max });
    SDL_RenderLine(renderer, min.x, min.y, max.x, min.y);
    SDL_RenderLine(renderer, max.x, min.y, max.x, max.y);
    SDL_RenderLine(renderer, max.x, max.y, min.x, max.y);
    SDL_RenderLine(renderer, min.x, max.y, min.x, min.y);
  }

public:
  inline void Render(MyScene& scene)
  {

    SDL_SetRenderDrawColor(renderer, 15, 15, 15, 255);
    SDL_RenderClear(renderer);

    for (int i = 0; i < scene.GetCircles().size(); ++i) {
      const auto [r, g, b, a] = scene.GetColor(i);
      SDL_SetRenderDrawColor(renderer, r, g, b, a);
      DrawCircle(renderer, scene.GetCircle(i));
      // DrawAABB(renderer, MakeAABB(scene.GetCircle(i)));
    }

    SDL_RenderPresent(renderer);
  }
};
