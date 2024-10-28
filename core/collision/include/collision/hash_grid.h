#pragma once

#include "./definitions.h"
#include "./query_iterable.h"

#include <base.h>

#include <unordered_map>
#include <unordered_set>

struct [[maybe_unused]] HashGrid
{
  std::unordered_set<IndexPair> keys{};
  std::unordered_multimap<IndexPair, Index> data{};

  [[maybe_unused]] inline void Push(Index id, Circle circle) noexcept
  {
    const auto key = Quantify(circle.AABB().min);
    keys.emplace(key);
    data.emplace(key, id);
  }

  [[maybe_unused]] inline void Push(Index id, DynamicCircle dynamic) noexcept
  {
    const auto key = Quantify(dynamic.AABB().min);
    keys.emplace(key);
    data.emplace(key, id);
  }

  [[maybe_unused]] inline void Reserve(Index size) noexcept
  {
    keys.reserve(size);
    data.reserve(size);
  }

  [[nodiscard]] [[maybe_unused]] constexpr inline static auto Neighbours(IndexPair x) noexcept
  {
    const auto n0 = x + IndexPair{ 1, 0 };
    const auto n1 = x + IndexPair{ -1, 1 };
    const auto n2 = x + IndexPair{ 0, 1 };
    const auto n3 = x + IndexPair{ 1, 1 };
    return std::array{ n0, n1, n2, n3 };
  }

  [[nodiscard]] [[maybe_unused]] inline auto Query(IndexPair key) noexcept
  {
    auto [beg, end] = data.equal_range(key);
    return QueryIterable{ beg, end };
  }

  [[nodiscard]] [[maybe_unused]] inline auto Query(const auto& circles, auto consumer) noexcept
  {
    std::vector<decltype(DynamicCircle{}.AABB())> aabbs{};
    std::vector<decltype(DynamicCircle{}.R45BB())> r45bbs{};
    aabbs.reserve(circles.size());
    r45bbs.reserve(circles.size());
    for (auto circle : circles) {
      aabbs.push_back(circle.AABB());
      r45bbs.push_back(circle.R45BB());
    }

    for (auto key : keys) {

      // pairs within a bucket
      const auto [beg, end] = data.equal_range(key);
      for (auto i = beg; i != end; ++i)
        for (auto j = std::next(i); j != end; ++j)
          if (MayOverlap(aabbs[i->second], aabbs[j->second]) && MayOverlap(r45bbs[i->second], r45bbs[j->second]))
            consumer(i->second, j->second);

      // pairs within neighbourhood
      for (auto neighbour : HashGrid::Neighbours(key)) {
        for (auto i : Query(neighbour))
          for (auto j : Query(key))
            if (MayOverlap(aabbs[i.second], aabbs[j.second]) && MayOverlap(r45bbs[i.second], r45bbs[j.second]))
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
