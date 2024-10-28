#pragma once

#include <collision.h>
#include <platform.h>

class MyWindow : public RendererWindow
{
protected:
  static inline Vec2<float> Transform(Vec2<float> vec)
  {
    constexpr auto factor = 3.63f;
    constexpr auto offset = Vec2<float>{ max_extend, max_extend };
    return factor * offset + (factor * vec);
  }

  static inline void DrawCircle(SDL_Renderer* renderer, DynamicCircle circle)
  {
    constexpr int n = 15;

    Vec2<float> a = Transform(Vec2<float>{ circle.p } + Vec2<float>{ circle.r, 0.0f });
    for (int i = 1; i <= n; ++i) {
      auto theta = (static_cast<float>(i) * 2.0f * std::numbers::pi_v<float>) / static_cast<float>(n);
      Vec2<float> b = Transform(Vec2<float>{ circle.p } + Vec2<float>{ circle.r * std::cos(theta), circle.r * std::sin(theta) });
      SDL_RenderLine(renderer, a.x, a.y, b.x, b.y);
      a = b;
    }
  }

  template<typename MinX, typename MinY, typename MaxX, typename MaxY>
  static inline void DrawAABB(SDL_Renderer* renderer, AABB<MinX, MinY, MaxX, MaxY> c)
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

    for (int i = 0; i < scene.GetLines().size(); ++i) {
      const auto [r, g, b, a] = scene.GetColor(i % scene.GetCircles().size());
      SDL_SetRenderDrawColor(renderer, r, g, b, a);
      const auto p0 = Transform(Vec2<float>{ scene.GetLine(i).p });
      const auto p1 = Transform(Vec2<float>{ scene.GetLine(i).p + scene.GetLine(i).e });
      SDL_RenderLine(renderer, p0.x, p0.y, p1.x, p1.y);
    }

    SDL_RenderPresent(renderer);
  }
};
