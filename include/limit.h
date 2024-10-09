#pragma once

#include <bit>
#include <cmath>

namespace limit {

constexpr float min_extend = 0.5f;
constexpr float max_extend = 2.0f;
constexpr float max_velocity = 2.0f;
constexpr float max_hull_extend = max_extend + max_velocity;

constexpr unsigned short quantization_shift = std::bit_width(static_cast<int>(max_hull_extend) - 1u);

}
