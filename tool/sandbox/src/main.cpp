#include "./game.h"
#include "./window.h"
#include "platform/utility.h"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_timer.h>

int
main(int /*unused*/, char** /*unused*/)
{
  auto runtime = Runtime{};
  auto network = Network{};
  auto window = MyWindow{};

  auto scene = MyScene{};
  auto game = MyGame{};

  Runtime::Init();
  Network::Init();
  window.Init();

  constexpr auto number_of_circles = 1 << 9; // MAX 11
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

    SDL_Log("%f fps; update: %lu ns \n", 1000.0 / (static_cast<double>(ti - t0) / 1000000.0), t_end - t_beg); // NOLINT(*-magic-numbers)
    SDL_Delay(12);

    t0 = ti;

    window.PollEvents([&quit](auto* event) {
      if (event->type == SDL_EVENT_QUIT) {
        quit = true;
      }
      if (event->type == SDL_EVENT_KEY_DOWN && event->key.key == SDLK_ESCAPE) {
        SoftExit();
      }

      return true; // process all present events
    });

  } while (!quit);
}
