#pragma once

#include "./vec2.h"
#include "./vec3.h"
#include "./vec4.h"

#include <cmath>

#include <cnl/elastic_integer.h>
#include <cnl/fixed_point.h>

using Float = cnl::fixed_point<cnl::elastic_integer<23, std::int32_t>, -10>;
using Vec2F = Vec2<Float>;
using Vec3F = Vec3<Float>;
using Vec4F = Vec4<Float>;

constexpr auto c0 = cnl::fixed_point<cnl::elastic_integer<0, std::int8_t>, 0>{ 0.0f };
constexpr auto c_125 = cnl::fixed_point<cnl::elastic_integer<1, std::int8_t>, -3>{ 0.125f };
constexpr auto c_25 = cnl::fixed_point<cnl::elastic_integer<1, std::int8_t>, -2>{ 0.25f };
constexpr auto c_5 = cnl::fixed_point<cnl::elastic_integer<1, std::int8_t>, -1>{ 0.5f };
constexpr auto c1 = cnl::fixed_point<cnl::elastic_integer<1, std::int8_t>, 0>{ 1.0f };
constexpr auto c2 = cnl::fixed_point<cnl::elastic_integer<1, std::int8_t>, 1>{ 2.0f };
constexpr auto c4 = cnl::fixed_point<cnl::elastic_integer<1, std::int8_t>, 2>{ 4.0f };
constexpr auto c8 = cnl::fixed_point<cnl::elastic_integer<1, std::int8_t>, 0>{ 8.0f };
constexpr auto c16 = cnl::fixed_point<cnl::elastic_integer<1, std::int8_t>, 1>{ 16.0f };
constexpr auto c32 = cnl::fixed_point<cnl::elastic_integer<1, std::int8_t>, 2>{ 32.0f };
constexpr auto c64 = cnl::fixed_point<cnl::elastic_integer<1, std::int8_t>, 2>{ 64.0f };
constexpr auto c128 = cnl::fixed_point<cnl::elastic_integer<1, std::int8_t>, 2>{ 128.0f };
constexpr auto c256 = cnl::fixed_point<cnl::elastic_integer<1, std::int8_t>, 2>{ 256.0f };

[[nodiscard]] constexpr inline auto
Sqrt(auto s) noexcept
{
  return cnl::sqrt(s);
}

[[nodiscard]] constexpr inline auto
Abs(auto s) noexcept
{
  return cnl::abs(s);
}
