#pragma once

#include <coroutine>
#include <unordered_map>
#include <unordered_set>

#include <absl/container/flat_hash_set.h>

#include <accelerator/constraint.h>
#include <container/query_iterable.h>
#include <geometry/aabb.h>
#include <type/index.h>

struct [[maybe_unused]] HashGrid
{
  absl::flat_hash_set<IndexPair, IndexPairHash> keys{};
  std::unordered_multimap<IndexPair, Index, IndexPairHash> data{};

  [[maybe_unused]] inline void Push(Index id, Circle circle) noexcept
  {
    const auto key = constraint::Quantify(MinAABB(circle));
    keys.insert(key);
    data.insert({ key, id });
  }

  [[maybe_unused]] inline void Push(Index id, Dynamic dynamic) noexcept
  {
    const auto key = constraint::Quantify(MinAABB(dynamic));
    keys.insert(key);
    data.insert({ key, id });
  }

  [[maybe_unused]] inline void Reserve(Index size) noexcept
  {
    keys.reserve(size);
    data.reserve(size);
  }

  [[nodiscard]] [[maybe_unused]] constexpr inline static auto Neighbours(IndexPair x) noexcept
  {
    return std::array{ x + IndexPair(1, 0), x + IndexPair(-1, 1), x + IndexPair(0, 1), x + IndexPair(1, 1) };
  }

  [[nodiscard]] [[maybe_unused]] inline auto Query(IndexPair key) noexcept
  {
    auto [beg, end] = data.equal_range(key);
    return QueryIterable{ beg, end };
  }

  [[nodiscard]] [[maybe_unused]] inline auto Query(const auto& circles, auto consumer) noexcept
  {
    std::vector<decltype(MakeAABB(Dynamic{}))> aabbs{};
    aabbs.reserve(circles.size());
    for (auto circle : circles)
      aabbs.push_back(MakeAABB(circle));

    for (auto key : keys) {

      // pairs within a bucket
      const auto [beg, end] = data.equal_range(key);
      for (auto i = beg; i != end; ++i)
        for (auto j = std::next(i); j != end; ++j)
          if (MayCollide(aabbs[i->second], aabbs[j->second]))
            consumer(i->second, j->second);

      // pairs within neighbourhood
      for (auto neighbour : HashGrid::Neighbours(key)) {
        for (auto i : Query(neighbour))
          for (auto j : Query(key))
            if (MayCollide(aabbs[i.second], aabbs[j.second]))
              consumer(i.second, j.second);
      }
    }
  }

  void Clear()
  {
    keys.clear();
    data.clear();
  }
};