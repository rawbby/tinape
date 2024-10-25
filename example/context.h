#pragma once

#include "game.h"
#include "scene.h"

#include <SDL3/SDL.h>
#include <SDL3_net/SDL_net.h>

#include <cstdlib>

struct Context
{
  bool quit = false;
  SDL_Window* window = nullptr;
  SDL_Renderer* renderer = nullptr;
  const int port = 0;
  SDLNet_Address* address = nullptr;
  SDLNet_DatagramSocket* socket = nullptr;
  Scene* scene = nullptr;
  Game* game = nullptr;
};

void
PollEvents(Context* context)
{
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_EVENT_QUIT)
      context->quit = true;
    HandleEvent(context->game, &event);
  }
}

void
PollDatagrams(Context* context)
{
  SDLNet_Datagram* datagram = nullptr;

  do {
    if (SDLNet_ReceiveDatagram(context->socket, &datagram)) {
      SDL_Log("UDP socket failed at system level\n");
      context->quit = true;
    }
    if (!datagram)
      return;

    HandleDatagram(context->game, datagram);
    SDLNet_DestroyDatagram(datagram);
  } while (true);
}

void
Init(Context* context)
{
  constexpr auto sdl_components = SDL_INIT_EVENTS | SDL_INIT_VIDEO | SDL_INIT_AUDIO;

  if (!SDL_Init(sdl_components)) {
    SDL_Log("SDL_Init failed: %s\n", SDL_GetError());
    std::exit(1);
  }

  if (SDLNet_Init()) {
    SDL_Log("SDLNet_Init failed: %s\n", SDL_GetError());
    SDL_Quit();
    std::exit(1);
  }

  context->window = SDL_CreateWindow("", 0, 0, SDL_WINDOW_HIDDEN | SDL_WINDOW_VULKAN);
  if (!context->window) {
    SDL_Log("SDL_CreateWindow failed: %s\n", SDL_GetError());
    SDLNet_Quit();
    SDL_Quit();
    std::exit(1);
  }

  auto vulkan_driver_found = false;
  for (int i = 0; i < SDL_GetNumRenderDrivers(); ++i)
    if (!strcmp(SDL_GetRenderDriver(i), "vulkan"))
      vulkan_driver_found = true;

  if (!vulkan_driver_found) {
    SDL_Log("vulkan renderer driver not found\n");
    SDL_DestroyWindow(context->window);
    SDLNet_Quit();
    SDL_Quit();
    std::exit(1);
  }

  context->renderer = SDL_CreateRenderer(context->window, "vulkan");
  if (!context->renderer) {
    SDL_Log("SDL_CreateRenderer failed: %s\n", SDL_GetError());
    SDL_DestroyWindow(context->window);
    SDLNet_Quit();
    SDL_Quit();
    std::exit(1);
  }

  const auto display = SDL_GetDisplayForWindow(context->window);
  const auto display_mode = SDL_GetCurrentDisplayMode(display);

  bool status = true;
  status &= SDL_SetWindowSize(context->window, display_mode->w, display_mode->h);
  status &= SDL_SetWindowFullscreenMode(context->window, display_mode);
  status &= SDL_SetWindowFullscreen(context->window, true);
  status &= SDL_SetWindowBordered(context->window, false);
  status &= SDL_ShowWindow(context->window);

  if (!status) {
    SDL_Log("SDL failed to show window: %s\n", SDL_GetError());
    SDL_DestroyWindow(context->window);
    SDLNet_Quit();
    SDL_Quit();
    std::exit(1);
  }

  context->address = SDLNet_ResolveHostname("::1");
  if (SDLNet_WaitUntilResolved(context->address, 5000) < 0) {
    SDL_Log("SDLNet_WaitUntilResolved failed: %s\n", SDL_GetError());
    SDL_DestroyWindow(context->window);
    SDLNet_Quit();
    SDL_Quit();
    std::exit(1);
  }

  context->socket = SDLNet_CreateDatagramSocket(context->address, 16002);
  if (!context->socket) {
    SDL_Log("SDLNet_CreateDatagramSocket failed: %s\n", SDL_GetError());
    SDL_DestroyWindow(context->window);
    SDLNet_Quit();
    SDL_Quit();
    std::exit(1);
  }

  context->scene = CreateScene(context);
  if (!context->scene) {
    SDL_Log("CreateScene failed!\n");
    SDLNet_DestroyDatagramSocket(context->socket);
    SDL_DestroyWindow(context->window);
    SDLNet_Quit();
    SDL_Quit();
    std::exit(1);
  }

  context->game = CreateGame(context, context->scene);
  if (!context->game) {
    SDL_Log("CreateGame failed!\n");
    DestroyScene(context->scene);
    SDLNet_DestroyDatagramSocket(context->socket);
    SDL_DestroyWindow(context->window);
    SDLNet_Quit();
    SDL_Quit();
    std::exit(1);
  }
}

void
Loop(Context* context)
{
  constexpr auto dt = static_cast<float>(20'000'000);
  auto t0 = SDL_GetTicksNS();

  do {
    const auto ti = SDL_GetTicksNS();
    RenderScene(context->scene, context->renderer);

    const auto t_beg = SDL_GetTicksNS();
    Update(context->game, static_cast<float>(ti - t0) / dt);
    const auto t_end = SDL_GetTicksNS();

    SDL_Log("%f fps; update: %lu ns \n", 1000.0 / (static_cast<double>(ti - t0) / 1000000.0), t_end - t_beg);
    SDL_Delay(20);

    t0 = ti;

    PollDatagrams(context);
    PollEvents(context);

  } while (!context->quit);
}

void
Quit(Context* context)
{
  DestroyGame(context->game);
  context->game = nullptr;

  SDLNet_DestroyDatagramSocket(context->socket);
  context->socket = nullptr;

  SDL_DestroyWindow(context->window);
  context->window = nullptr;

  SDLNet_Quit();
  SDL_Quit();
}
