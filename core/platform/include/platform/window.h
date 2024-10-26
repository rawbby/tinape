#pragma once

#include "log.h"

#include <SDL3/SDL.h>

class Window
{
protected:
  SDL_Window* handle = nullptr;

public:
  Window() = default;

  virtual bool Init()
  {
    handle = SDL_CreateWindow("", 0, 0, SDL_WINDOW_HIDDEN | SDL_WINDOW_VULKAN);
    if (!handle) {
      Log("SDL_CreateWindow failed: %s\n", SDL_GetError());
      return false;
    }

    const auto display = SDL_GetDisplayForWindow(handle);
    const auto display_mode = SDL_GetCurrentDisplayMode(display);

    bool status = true;
    status &= SDL_SetWindowSize(handle, display_mode->w, display_mode->h);
    status &= SDL_SetWindowFullscreenMode(handle, display_mode);
    status &= SDL_SetWindowFullscreen(handle, true);
    status &= SDL_SetWindowBordered(handle, false);
    status &= SDL_ShowWindow(handle);

    if (!status) {
      Log("SDL failed to show handle: %s\n", SDL_GetError());
      SDL_DestroyWindow(handle);
      handle = nullptr;
      return false;
    }

    return true;
  }

  inline void PollEvents(auto callback)
  {
    SDL_Event event;
    while (SDL_PollEvent(&event) && callback(&event))
      ;
  }

  ~Window()
  {
    if (handle)
      SDL_DestroyWindow(handle);
  }
};

class RendererWindow : public Window
{
protected:
  SDL_Renderer* renderer = nullptr;

public:
  RendererWindow() = default;

  bool Init() override
  {
    Window::Init();

    auto vulkan_driver_found = false;
    for (int i = 0; i < SDL_GetNumRenderDrivers(); ++i)
      if (!strcmp(SDL_GetRenderDriver(i), "vulkan"))
        vulkan_driver_found = true;

    if (!vulkan_driver_found) {
      Log("vulkan renderer driver not found\n");
      SDL_DestroyWindow(handle);
      handle = nullptr;
      return false;
    }

    renderer = SDL_CreateRenderer(handle, "vulkan");
    if (!renderer) {
      Log("SDL_CreateRenderer failed: %s\n", SDL_GetError());
      SDL_DestroyWindow(handle);
      handle = nullptr;
      return false;
    }

    return true;
  }

  ~RendererWindow()
  {
    if (renderer)
      SDL_DestroyRenderer(renderer);
    Window::~Window();
  }
};
