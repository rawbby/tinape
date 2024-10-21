#include "./game.h"
#include "./random.h"
#include "./scene.h"

#include <accelerator/adjacency_list.h>
#include <accelerator/hash_grid.h>

#include <geometry/circle.h>
#include <geometry/math.h>

#include <index/index.h>

#include <unordered_map>
#include <unordered_set>
#include <vector>

struct Game
{
  Context* context = nullptr;
  Scene* scene = nullptr;
};

Game*
CreateGame(Context* context, Scene* scene)
{
  auto game = static_cast<Game*>(SDL_aligned_alloc(sizeof(Game), 4096));
  if (game) {
    game->context = context;
    game->scene = scene;
  }
  return game;
}

void
DestroyGame(Game* game)
{
  SDL_aligned_free(game);
}

// void
// handle_island(std::vector<Dynamic>& circles, std::vector<Index>& island, std::unordered_map<Index, Index>& island_edges)
// {
//   auto steps = static_cast<int>(std::ceil(2.0f * limit::max_velocity / limit::min_extend));
//
//   for (int i = 0; i < steps; ++i) {
//     auto dt = 1.0f / static_cast<float>(steps - i);
//
//     auto sliding_velocities = std::unordered_map<Index, FV>{};
//
//     for (auto v : island) {
//       bool sliding = false;
//       auto sliding_d = FV{};
//
//       const auto cv = circles[v];
//       const auto cvv = cv.v * dt;
//       const auto cvp = cv.p + cvv;
//
//       for (auto [_, w] : Range(island_edges.equal_range(v))) {
//         const auto cw = circles[w];
//         const auto d = (cw.p + cw.v * dt) - cvp;
//         const auto rr = cw.r + cv.r;
//
//         if (Dot(d, d) < rr * rr && Dot(d, cvv) > 0.0f) {
//           if (sliding)
//             goto SKIP_BLOCKED_V;
//
//           sliding = true;
//           sliding_d = d;
//         }
//       }
//
//       if (sliding) // handle sliding later
//         sliding_velocities.emplace(v, VecRejection(cvv, sliding_d));
//       else // advance as there are no collisions
//         circles[v].p += cvv;
//
//       // ignore this velocity as v is blocked
//     SKIP_BLOCKED_V:;
//       circles[v].v -= cvv;
//     }
//
//     for (auto [v, cvv] : sliding_velocities) {
//       const auto cv = circles[v];
//       const auto cvp = cv.p + cvv;
//
//       for (auto [_, w] : Range(island_edges.equal_range(v))) {
//         const auto cw = circles[w];
//         const auto d = cw.p - cvp;
//         const auto rr = cw.r + cv.r;
//
//         if (Dot(d, d) < rr * rr)
//           goto CANCEL_SLIDING_V;
//       }
//
//       // advance with sliding
//       circles[v].p += cvv;
//
//       // ignore this sliding as it is blocked
//     CANCEL_SLIDING_V:;
//     }
//   }
// }

bool
IsBlockingContinuous(Dynamic a, Dynamic b)
{
  const auto a_ = Dynamic{ a.p, a.r, Vec2F{} }; // in case `a` is stopped later
  const auto b_ = Dynamic{ b.p, b.r, Vec2F{} }; // in case `b` is stopped later
  return DoCollide(a, b) || DoCollide(a_, b) || DoCollide(a, b_);
}

bool
IsBlockingStepping(Dynamic a, Dynamic b)
{
  const auto ci0 = Circle{ a.p, a.r };
  const auto cj0 = Circle{ b.p, b.r };
  const auto ci5 = Circle{ a.p + 0.5f * a.v, a.r };
  const auto cj5 = Circle{ b.p + 0.5f * b.v, b.r };
  const auto ci1 = Circle{ a.p + a.v, a.r };
  const auto cj1 = Circle{ b.p + b.v, b.r };
  // clang-format off
  return Overlap(ci0, cj0) || Overlap(ci0, cj5) || Overlap(ci0, cj1)
      || Overlap(ci5, cj0) || Overlap(ci5, cj5) || Overlap(ci5, cj1)
      || Overlap(ci1, cj0) || Overlap(ci1, cj5) || Overlap(ci1, cj1);
  // clang-format on
}

void
HandleIsland(Scene* scene, std::vector<Dynamic>& circles, std::vector<Index>& island, std::unordered_multimap<Index, Index>& island_edges)
{
  const auto n = island.size();
  std::unordered_set<Index> blocked{};

  for (auto [i, j] : island_edges) {
    if (IsBlockingStepping(circles[i], circles[j])) {
      blocked.insert(i);
      blocked.insert(j);
    }
  }

  for (int i = 0; i < n; ++i) {
    if (!blocked.contains(island[i]))
      circles[island[i]].p += circles[island[i]].v;
    circles[island[i]].v = Vec2F{};
  }
}

void
BruteForce(std::vector<Dynamic>& circles)
{
  const auto n = circles.size();
  std::vector<bool> blocked{};
  blocked.resize(n, false);

  for (int i = 0; i < n; ++i)
    for (int j = i + 1; j < n; ++j)
      if (IsBlockingStepping(circles[i], circles[j]))
        blocked[i] = blocked[j] = true;

  for (int i = 0; i < n; ++i) {
    if (!blocked[i])
      circles[i].p += circles[i].v;
    circles[i].v = Vec2F{};
  }
}

void
Update(Game* game, float)
{
  auto& circles = Circles(game->scene);

  HashGrid grid{};
  grid.Reserve(circles.size());
  for (int i = 0; i < circles.size(); ++i)
    grid.Push(i, circles[i]);

  AdjacencyList archipelago{};
  grid.Query(circles, [&](auto i, auto j) {
    archipelago.AddEdge(i, j);
  });
  archipelago.QueryIslands([&](auto island, auto edges) {
    HandleIsland(game->scene, circles, island, edges);
  });

  auto& random = GetRandom(game->scene);
  for (auto& circle : circles) {
    circle.p += circle.v;

    if (circle.v == Vec2F{})
      circle.v = random.random_velocity();

    if (circle.p.x < c0)
      circle.v.x = random.random_bool() ? constraint::max_velocity_f : 0.0f;
    if (circle.p.x > constraint::world_width)
      circle.v.x = random.random_bool() ? -constraint::max_velocity_f : 0.0f;
    if (circle.p.y < c0)
      circle.v.y = random.random_bool() ? constraint::max_velocity_f : 0.0f;
    if (circle.p.y > constraint::world_height)
      circle.v.y = random.random_bool() ? -constraint::max_velocity_f : 0.0f;
  }
}

void
HandleDatagram(Game*, SDLNet_Datagram*)
{
}

void
HandleEvent(Game*, SDL_Event* event)
{
  if (event->type == SDL_EVENT_KEY_DOWN)
    switch (event->key.key) {
      case SDLK_ESCAPE: {
        SDL_Event quit_request{ .quit = { SDL_EVENT_QUIT, 0, SDL_GetTicksNS() } };
        SDL_PushEvent(&quit_request);
      }
      default:
        break;
    }
}
