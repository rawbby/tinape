#include "circle.h"
#include "index.h"
#include "limit.h"
#include "random.h"

#include <array>
#include <iostream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

template<typename Iterator>
struct Range
{
  Iterator m_begin;
  Iterator m_end;

  Range(Iterator begin, Iterator end)
    : m_begin(std::move(begin))
    , m_end(std::move(end))
  {
  }

  Range(std::pair<Iterator, Iterator> pair) // NOLINT(*-explicit-constructor)
    : m_begin(std::move(pair.first))
    , m_end(std::move(pair.second))
  {
  }

  [[nodiscard]] Iterator begin() const
  {
    return m_begin;
  }

  [[nodiscard]] Iterator end() const
  {
    return m_end;
  }
};

struct Grid
{
  std::unordered_set<IndexPair> keys{};
  std::unordered_multimap<IndexPair, Index> data{};

  void push(Index id, AABB aabb)
  {
    const auto x = static_cast<Index>(static_cast<Index>(aabb.min.x) >> limit::quantization_shift);
    const auto y = static_cast<Index>(static_cast<Index>(aabb.min.y) >> limit::quantization_shift);

    auto key = IndexPair{ x, y };
    keys.insert(key);
    data.insert({ key, id });
  }

  void insert(const auto& container)
  {
    Index id = 0;
    for (auto element : container) {
      push(id, element);
      ++id;
    }
  }

  auto range(IndexPair key)
  {
    auto [beg, end] = data.equal_range(key);
    return Range{ beg, end };
  }

  static auto neighbours(IndexPair x)
  {
    return std::array{ x.add(1, 0), x.add(-1, 1), x.add(0, 1), x.add(1, 1) };
  }
};

struct AdjacencyList
{
  std::unordered_set<Index> keys{};
  std::unordered_multimap<Index, Index> data{};
  void add_edge(Index a, Index b)
  {
    keys.insert(a);
    keys.insert(b);
    data.insert({ a, b });
    data.insert({ b, a });
  }
  auto range(Index key)
  {
    auto [beg, end] = data.equal_range(key);
    return Range{ beg, end };
  }
};

void
handle_island(std::vector<Dynamic>& circles, std::vector<Index>& island, std::unordered_set<IndexPair>& island_edges)
{
  std::unordered_map<Index, Vec> sliding{};
  std::unordered_map<Index, bool> blocked{};

  auto steps = std::ceil(2.0f * limit::max_velocity / limit::min_extend);
  auto dt = 1.0f / steps;

  for (float t = dt; t <= 1.0f; t += dt) { // NOLINT(*-flp30-c)

    for (auto [v, w] : island_edges) {

      auto cv = circles[v];
      auto cw = circles[w];
      auto cva = advance(cv, dt);
      auto cwa = advance(cw, dt);

      if (overlap(cva, cwa)) {
        const auto diff = cwa.p - cva.p;

        if (!blocked[v] && glm::dot(diff, cv.v) > 0.0f) {
          const auto find = sliding.find(v);
          if (find == sliding.end()) {
            sliding.insert({ v, VecRejection(dt * cv.v, diff) });
          } else {
            sliding.erase(find);
            blocked[v] = true;
          }
        }

        if (!blocked[v] && glm::dot(diff, cw.v) < 0.0f) {
          const auto find = sliding.find(w);
          if (find == sliding.end()) {
            sliding.insert({ w, VecRejection(dt * cw.v, diff) });
          } else {
            sliding.erase(find);
            blocked[w] = true;
          }
        }
      }
    }

    for (auto [v, vel] : sliding) {
      if (!sliding[v] || blocked[v])
        continue;

      auto cv = circles[v];
      cv.p += velocity[v];

      for (auto [_, w] : Range(island_edges.equal_range(v))) {
        auto cw = circles[w];
        if (sliding[w] && !blocked[w])
          cw.p += velocity[w];
      }
    }
  }
}

bool
may_collide(const std::vector<Dynamic>& circles, Index a, Index b)
{
  return may_overlap(circles[a], circles[b]);
}

int
main()
{
  std::vector<Dynamic> circles{};
  Random{}.fill_random_circles(circles, 16 * 1024);

  Grid grid{};
  grid.insert(circles);

  AdjacencyList maybe_collisions{};

  // check if collision possible locally
  unsigned check_count = 0;
  for (auto key : grid.keys) {
    auto [beg, end] = grid.data.equal_range(key);
    for (auto i = beg; i != end; ++i) {
      auto j = i;
      while (++j != end) {
        ++check_count;
        if (may_collide(circles, i->second, j->second))
          maybe_collisions.add_edge(i->second, j->second);
      }
    }
    for (auto neighbour : Grid::neighbours(key)) {
      for (auto i : grid.range(neighbour)) {
        for (auto j : grid.range(key)) {
          ++check_count;
          if (may_collide(circles, i.second, j.second))
            maybe_collisions.add_edge(i.second, j.second);
        }
      }
    }
  }

  // DFS for islands
  std::stack<Index> s{};
  std::vector<Index> island{};
  std::unordered_set<IndexPair> island_edges{};
  while (!maybe_collisions.keys.empty()) {
    s.push(*maybe_collisions.keys.begin());
    while (!s.empty()) {
      auto v = s.top();
      s.pop();
      if (maybe_collisions.keys.erase(v)) { // new
        island.push_back(v);
        for (auto [_, w] : maybe_collisions.range(v)) {
          s.push(w);
          island_edges.insert(make_sorted_index(v, w));
        }
      }
    }

    // handle island
    handle_island(circles, island, island_edges);
    island_edges.clear();
    island.clear();
  }

  std::size_t max = 0;
  for (auto key : grid.keys) {
    std::size_t count = 0;
    for ([[maybe_unused]] auto _ : grid.range(key))
      ++count;
    max = std::max(count, max);
  }

  std::cout << "Checks:   " << check_count << " instead of " << circles.size() * circles.size() << std::endl;
}
