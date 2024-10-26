#pragma once

#include <container/query_iterable.h>
#include <type/index.h>

#include <absl/container/flat_hash_set.h>
#include <absl/container/inlined_vector.h>

#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

struct AdjacencyList
{
  absl::flat_hash_set<Index, IndexHash> keys{};
  std::unordered_multimap<Index, Index> data{};

  [[maybe_unused]] inline void AddEdge(Index a, Index b) noexcept
  {
    keys.insert(a);
    keys.insert(b);
    data.insert({ a, b });
    data.insert({ b, a });
  }

  [[nodiscard]] [[maybe_unused]] inline auto Query(Index key) noexcept
  {
    auto [beg, end] = data.equal_range(key);
    return QueryIterable{ beg, end };
  }

  [[nodiscard]] [[maybe_unused]] inline auto QueryIslands(auto consumer) noexcept
  {
    // DFS

    absl::InlinedVector<Index, 64> stack{};
    absl::InlinedVector<Index, 64> island{};
    std::unordered_multimap<Index, Index> island_edges{};

    while (!keys.empty()) {
      stack.push_back(*keys.begin());
      while (!stack.empty()) {
        auto v = Index{ stack.back() };
        stack.pop_back();
        if (keys.erase(v)) {
          island.push_back(v);
          for (auto [_, w] : Query(v)) {
            stack.push_back(w);
            island_edges.emplace(v, w);
          }
        }
      }

      consumer(island, island_edges);

      island_edges.clear();
      island.clear();
    }
  }

  void Clear()
  {
    keys.clear();
    data.clear();
  }
};
