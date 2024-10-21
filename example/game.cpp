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

// bool
// may_collide_(Dynamic ci, Dynamic cj)
// {
//   const auto cia = Advance(ci);
//   const auto cja = Advance(cj);
//   const auto ci_ = Dynamic{ cia.p, cia.r, C<F, F>{ 0.0f, 0.0f } };
//   const auto cj_ = Dynamic{ cja.p, cja.r, C<F, F>{ 0.0f, 0.0f } };
//
//   const auto cit = CollisionInTime(ci, cj);
//   const auto cit1 = CollisionInTime(ci_, cj); // in case ci is stopped later
//   const auto cit2 = CollisionInTime(ci, cj_); // in case cj is stopped later
//   const auto col = Overlap(cia, cja);
//
//   if (cit == -1)
//     SDL_Log("Circles overlap at 0");
//
//   if (col && !cit)
//     SDL_Log("col && !cit\n");
//
//   return cit || cit1 || cit2 || col;
// }

void
HandleIsland(Scene* scene, std::vector<Dynamic>& circles, std::vector<Index>& island, std::unordered_multimap<Index, Index>& island_edges)
{
  const auto rc = Random{}.random_color();
  SDL_Color c{
    .r = static_cast<Uint8>(rc.r),
    .g = static_cast<Uint8>(rc.g),
    .b = static_cast<Uint8>(rc.b),
    .a = static_cast<Uint8>(255),
  };

  const auto n = island.size();
  std::unordered_set<Index> blocked{};

  for (auto [i, j] : island_edges) {
    const auto ci = circles[i];
    const auto cj = circles[j];
    const auto ci_ = Dynamic{ ci.p, ci.r, Vec2F{} };
    const auto cj_ = Dynamic{ cj.p, cj.r, Vec2F{} };

    const auto cit = DoCollide(ci, cj);
    const auto cit1 = DoCollide(ci_, cj); // in case ci is stopped later
    const auto cit2 = DoCollide(ci, cj_); // in case cj is stopped later

    if (cit || cit1 || cit2) {
      blocked.insert(i);
      blocked.insert(j);
    }
  }

  for (int i = 0; i < n; ++i) {
    SetColor(scene, island[i], c);
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
    for (int j = i + 1; j < n; ++j) {

      const auto ci = circles[i];
      const auto cj = circles[j];
      const auto ci_ = Dynamic{ ci.p, ci.r, Vec2F{} };
      const auto cj_ = Dynamic{ cj.p, cj.r, Vec2F{} };

      const auto cit = DoCollide(ci, cj);
      const auto cit1 = DoCollide(ci_, cj); // in case ci is stopped later
      const auto cit2 = DoCollide(ci, cj_); // in case cj is stopped later

      if (cit || cit1 || cit2)
        blocked[i] = blocked[j] = true;
    }

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

  // auto circles_ = Circles(game->scene);
  // BruteForce(circles_);

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

  auto random = Random{};
  for (auto& circle : circles) {
    circle.p += circle.v;

    if (circle.v == Vec2F{})
      circle.v = random.random_velocity();

    if (circle.p.x < c0)
      circle.v.x = c1;
    if (circle.p.x > constraint::world_width)
      circle.v.x = -c1;
    if (circle.p.y < c0)
      circle.v.y = c1;
    if (circle.p.y > constraint::world_height)
      circle.v.y = -c1;
  }

  // const auto n = circles.size();
  // for (int i = 0; i < n; ++i)
  //   if (circles[i].p != circles_[i].p)
  //     SDL_Log("Non default behaviour!");

  // Random{}.update_random_circles(Circles(game->scene));
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
