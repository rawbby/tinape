#pragma once

#include "./scene.h"

#include <collision.h>

class MyGame
{
protected:
  MyScene* scene = nullptr;

public:
  MyGame() = default;

  bool Init(MyScene* scene_)
  {
    scene = scene_;
    return true;
  }

  static bool IsBlockingStepping(DynamicCircle a, DynamicCircle b, float dt)
  {
    const auto ci0 = Circle{ a.p, a.r };
    const auto cj0 = Circle{ b.p, b.r };
    const auto ci5 = Circle{ a.p + dt * a.v, a.r };
    const auto cj5 = Circle{ b.p + dt * b.v, b.r };
    // clang-format off
    return Overlap(ci0, cj0) || Overlap(ci0, cj5)
        || Overlap(ci5, cj0) || Overlap(ci5, cj5);
    // clang-format on
  }

  void HandleIsland(std::span<DynamicCircle> circles, std::span<Index> island, std::unordered_multimap<Index, Index>& island_edges)
  {
    const auto color = scene->RandomColor();

    const auto n = island.size();
    std::unordered_set<Index> blocked{};

    for (int _ = 0; _ < 8; ++_) {
      blocked.clear();

      for (auto [i, j] : island_edges) {
        if (IsBlockingStepping(circles[i], circles[j], 0.125F)) {
          blocked.insert(i);
          blocked.insert(j);
        }
      }

      for (int i = 0; i < n; ++i) {
        if (!blocked.contains(island[i])) {
          circles[island[i]].p += 0.125F * circles[island[i]].v;
        }
      }
    }

    for (int i = 0; i < n; ++i) {
      scene->GetColor(island[i]) = SDL_Color(color.r, color.g, color.b, 255);
      circles[island[i]].v = Vec2<Velocity>{};
    }
  }

  void Update()
  {
    auto circles = scene->GetCircles();

    static HashGrid grid{};
    grid.Clear();
    grid.Reserve(circles.size());
    for (int i = 0; i < circles.size(); ++i) {
      grid.Push(i, circles[i]);
    }

    static AdjacencyList archipelago{};
    archipelago.Clear();
    grid.Query(circles, [&](auto i, auto j) {
      archipelago.AddEdge(i, j);
    });
    archipelago.QueryIslands([&](auto island, auto edges) {
      HandleIsland(circles, island, edges);
    });

    for (auto& circle : circles) {
      circle.p += circle.v;

      if (circle.v == Vec2<Velocity>{} && scene->RandomBool() && scene->RandomBool() && scene->RandomBool() && scene->RandomBool()) {
        circle.v = scene->RandomVelocity();
      }

      if (circle.p.x < base::c0) {
        circle.v.x = scene->RandomBool() ? 2.0F : 0.0F;
      }
      if (circle.p.x > world_width) {
        circle.v.x = scene->RandomBool() ? -2.0F : 0.0F;
      }
      if (circle.p.y < base::c0) {
        circle.v.y = scene->RandomBool() ? 2.0F : 0.0F;
      }
      if (circle.p.y > world_height) {
        circle.v.y = scene->RandomBool() ? -2.0F : 0.0F;
      }
    }
  }

  ~MyGame() = default;
};
