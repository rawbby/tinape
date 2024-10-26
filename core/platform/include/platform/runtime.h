#pragma once

#include "log.h"

#include <SDL3/SDL.h>

class Runtime
{
public:
  Runtime() = default;

  inline bool Init()
  {
    if (!SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
      Log("SDL_Init failed: %s\n", SDL_GetError());
      return false;
    }

    return true;
  }

  ~Runtime()
  {
    SDL_Quit();
  }
};
