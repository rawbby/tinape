#pragma once

#include <geometry/circle.h>
#include <geometry/math.h>
#include <index/index.h>

#include <unordered_map>
#include <unordered_set>
#include <vector>

void
HandleIsland(std::vector<Dynamic>& circles, std::vector<Index>& island, std::unordered_map<Index, Index>& island_edges)
{
  for (auto i = 0; i < 10; ++i) {

    std::unordered_set<Index> no_collision{};
    no_collision.insert(island.begin(), island.end());

    for (auto [v, w] : island_edges) {
      const auto ci = circles[v];
      const auto cj = circles[w];
      const auto cia = Advance(ci);
      const auto cja = Advance(cj);
      const auto ci_ = Dynamic{ cia.p, cia.r, Vec2F{ 0.0f, 0.0f } };
      const auto cj_ = Dynamic{ cja.p, cja.r, Vec2F{ 0.0f, 0.0f } };
      const auto cit = DoCollide(ci, cj, 1.0f / 10.0f);
      const auto cit1 = DoCollide(ci_, cj, 1.0f / 10.0f); // in case ci is stopped later
      const auto cit2 = DoCollide(ci, cj_, 1.0f / 10.0f); // in case cj is stopped later

      if (cit || cit1 || cit2) {
        no_collision.erase(v);
        no_collision.erase(w);
        break;
      }
    }

    for (auto v : no_collision)
      circles[v].p += (1.0f / 10.0f) * circles[v].v;
  }

  for (auto v : island)
    circles[v].v = Vec2F{};
}
