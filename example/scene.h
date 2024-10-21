#pragma once

#include "./random.h"

#include <SDL3/SDL.h>
#include <geometry/circle.h>

struct Context;
struct Scene;

Scene*
CreateScene(Context*);

void
DestroyScene(Scene*);

std::vector<Dynamic>&
Circles(Scene*);

void
RenderScene(Scene*, SDL_Renderer*);

void
SetColor(Scene*, Uint32, SDL_Color);

SDL_Color
GetColor(Scene* scene, Uint32 index);

Random&
GetRandom(Scene* scene);
