#include "./game.h"
#include "./scene.h"

#include <type/float.h>
#include <type/vec2.h>

#include <platform.h>

#include <accelerator/constraint.h>
#include <geometry/aabb.h>
#include <geometry/circle.h>

#include <absl/container/inlined_vector.h>

class MyWindow : public RendererWindow
{
protected:
  inline auto Transform(auto vec)
  {
    constexpr auto factor = 3.63f / 8.0f;
    constexpr auto offset = Vec2<decltype(constraint::max_extend)>{ constraint::max_extend, constraint::max_extend };
    return factor * offset + (factor * vec);
  }

  inline void DrawCircle(SDL_Renderer* renderer, Dynamic circle)
  {
    constexpr int n = 15;

    Vec2<float> a = Transform(circle.p + Vec2F(circle.r, 0.0f));
    for (int i = 1; i <= n; ++i) {
      auto theta = static_cast<Float>(i) * 2 * cnl::numbers::pi_v<Float> / n;
      Vec2<float> b = Transform(circle.p + Vec2F(circle.r * cnl::cos(theta), circle.r * cnl::sin(theta)));
      SDL_RenderLine(renderer, a.x, a.y, b.x, b.y);
      a = b;
    }
  }

  template<typename S>
  inline void DrawAABB(SDL_Renderer* renderer, AABB<S> c)
  {
    Vec2<float, float> min = Transform(c.min);
    Vec2<float, float> max = Transform(c.max);
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

int
main(int, char**)
{
  auto runtime = Runtime{};
  auto network = Network{};
  auto window = MyWindow{};

  auto scene = MyScene{};
  auto game = MyGame{};

  runtime.Init();
  network.Init();
  window.Init();

  constexpr auto number_of_circles = 1 << 12;
  scene.Init(number_of_circles);
  game.Init(&scene);

  auto t0 = SDL_GetTicksNS();
  bool quit = false;
  do {
    const auto ti = SDL_GetTicksNS();
    window.Render(scene);

    const auto t_beg = SDL_GetTicksNS();
    game.Update();
    const auto t_end = SDL_GetTicksNS();

    SDL_Log("%f fps; update: %lu ns \n", 1000.0 / (static_cast<double>(ti - t0) / 1000000.0), t_end - t_beg);
    SDL_Delay(20);

    t0 = ti;

    window.PollEvents([&quit](auto* event) {
      if (event->type == SDL_EVENT_QUIT)
        quit = true;
      if (event->type == SDL_EVENT_KEY_DOWN && event->key.key == SDLK_ESCAPE)
        SoftExit();

      return true; // process all present events
    });

  } while (!quit);
}
