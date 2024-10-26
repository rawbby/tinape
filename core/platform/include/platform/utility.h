#pragma once

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_timer.h>

#include <cstdlib>

inline void
Exit(int code = 1)
{
  std::exit(code);
}

inline void
SoftExit()
{
  SDL_Event quit_request{ .quit = { SDL_EVENT_QUIT, 0, SDL_GetTicksNS() } };
  SDL_PushEvent(&quit_request);
}
