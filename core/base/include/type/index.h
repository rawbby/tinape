#pragma once

#include <cstdint>

#include <absl/hash/hash.h>

using Index = std::uint16_t;
using IndexHash = absl::Hash<std::uint32_t>;
