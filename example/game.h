#pragma once

#include <SDL3/SDL.h>
#include <SDL3_net/SDL_net.h>

struct Context;
struct Scene;
struct Game;

Game*
CreateGame(Context*, Scene*);

void
DestroyGame(Game*);

void
Update(Game*, float dt);

void
HandleDatagram(Game*, SDLNet_Datagram*);

void
HandleEvent(Game*, SDL_Event*);
