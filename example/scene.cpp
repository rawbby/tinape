#include "./scene.h"
#include "geometry/aabb.h"
#include <geometry/circle.h>

#include <vector>

#include "./random.h"

#include <glm/gtc/constants.hpp>

struct Scene
{
  Context* context = nullptr;
  std::vector<Dynamic>* circles = nullptr;
  std::vector<SDL_Color>* colors = nullptr;
};

Scene*
CreateScene(Context* context)
{
  auto random = Random{};
  auto scene = static_cast<Scene*>(SDL_aligned_alloc(sizeof(Scene), 4096));
  if (scene) {
    scene->circles = new std::vector<Dynamic>{};
    scene->colors = new std::vector<SDL_Color>{};

    scene->context = context;
    Random{}.fill_random_circles(*scene->circles, 1024);

    for (int i = 0; i < scene->circles->size(); ++i) {
      const auto c = random.random_color();
      const auto r = c.r;
      const auto g = c.g;
      const auto b = c.b;
      const auto a = 255;
      scene->colors->emplace_back(r, g, b, a);
    }
  }
  return scene;
}

std::vector<Dynamic>&
Circles(Scene* scene)
{
  return *scene->circles;
}

void
DestroyScene(Scene* scene)
{
  delete scene->circles;
  delete scene->colors;
  SDL_aligned_free(scene);
}

inline auto
Transform(auto vec)
{
  constexpr auto factor = 3.63f;
  constexpr auto offset = Vec<decltype(constraint::max_extend)>{ constraint::max_extend, constraint::max_extend };
  return factor * offset + (factor * vec);
}

inline void
DrawCircle(SDL_Renderer* renderer, Dynamic circle)
{
  constexpr int n = 45;

  Vec<float, float> a = Transform(circle.p + Vec2F(circle.r, 0.0f));
  for (int i = 1; i <= n; ++i) {
    auto theta = static_cast<Float>(i) * glm::two_pi<Float>() / n;
    Vec<float, float> b = Transform(circle.p + Vec2F(circle.r * cnl::cos(theta), circle.r * cnl::sin(theta)));
    SDL_RenderLine(renderer, a.x, a.y, b.x, b.y);
    a = b;
  }
}

template<typename S>
inline void
DrawAABB(SDL_Renderer* renderer, AABB<S> c)
{
  Vec<float, float> min = Transform(c.min);
  Vec<float, float> max = Transform(c.max);
  SDL_RenderLine(renderer, min.x, min.y, max.x, min.y);
  SDL_RenderLine(renderer, max.x, min.y, max.x, max.y);
  SDL_RenderLine(renderer, max.x, max.y, min.x, max.y);
  SDL_RenderLine(renderer, min.x, max.y, min.x, min.y);
}

void
RenderScene(Scene* scene, SDL_Renderer* renderer)
{
  SDL_SetRenderDrawColor(renderer, 15, 15, 15, 255);
  SDL_RenderClear(renderer);

  for (int i = 0; i < scene->circles->size(); ++i) {
    const auto [r, g, b, a] = (*scene->colors)[i];
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    DrawCircle(renderer, (*scene->circles)[i]);
    // DrawAABB(renderer, MakeAABB(scene->circles->at(i)));
  }

  SDL_RenderPresent(renderer);
}

void
SetColor(Scene* scene, Uint32 index, SDL_Color color)
{
  scene->colors->at(index) = color;
}

SDL_Color
GetColor(Scene* scene, Uint32 index)
{
  return scene->colors->at(index);
}
