#pragma once

#include <cnl/elastic_integer.h>
#include <cnl/scaled_integer.h>

#include <bit>
#include <numbers>

namespace base {

namespace internal {

template<int CONDITION, typename IF_TRUE, typename IF_FALSE>
constexpr auto
ConditionalType() noexcept
{
  if constexpr (CONDITION) {
    return IF_TRUE{};
  } else {
    return IF_FALSE{};
  }
}

template<int CONDITION, typename IF_TRUE, typename IF_FALSE>
using ConditionalTypeV = decltype(ConditionalType<CONDITION, IF_TRUE, IF_FALSE>());

template<int SIGNED, unsigned BITS>
constexpr auto
NarrowestInteger() noexcept
{
  constexpr int BITS_ = SIGNED + (BITS >> 3U) + (BITS & 0b111U ? 1U : 0U);
  if constexpr (BITS_ == 1U) {
    return ConditionalType<SIGNED, std::int8_t, std::uint8_t>();
  } else if constexpr (BITS_ <= 2U) {
    return ConditionalType<SIGNED, std::int16_t, std::uint16_t>();
  } else if constexpr (BITS_ <= 4U) {
    return ConditionalType<SIGNED, std::int32_t, std::uint32_t>();
  } else if constexpr (BITS_ <= 8U) { // NOLINT(*-magic-numbers)
    return ConditionalType<SIGNED, std::int64_t, std::uint64_t>();
  } else {
    return ConditionalType<SIGNED, __int128, unsigned __int128>();
  }
}

template<int SIGNED, int BITS>
using NarrowestIntegerV = decltype(NarrowestInteger<SIGNED, BITS>());

template<int POWER>
constexpr auto
PowerOfTwo() noexcept
{
  // use bit cast to allow every power of two representation using only one byte
  return std::bit_cast<cnl::scaled_integer<cnl::elastic_integer<1, std::uint8_t>, cnl::power<POWER, 2>>>(std::uint8_t{ 1 });
}

}

template<int SIGNED, int INTEGER, int PLACES>
using Fixed = cnl::scaled_integer<cnl::elastic_integer<INTEGER + PLACES, internal::NarrowestIntegerV<SIGNED, INTEGER + PLACES>>, cnl::power<-PLACES, 2>>;

constexpr auto c0 = cnl::scaled_integer<cnl::elastic_integer<0, std::uint8_t>, cnl::power<0, 2>>{ 0 };
constexpr auto c_000244141 = internal::PowerOfTwo<-12>();
constexpr auto c_000488281 = internal::PowerOfTwo<-11>();
constexpr auto c_000976563 = internal::PowerOfTwo<-10>();
constexpr auto c_00195313 = internal::PowerOfTwo<-9>();
constexpr auto c_00390625 = internal::PowerOfTwo<-8>();
constexpr auto c_0078125 = internal::PowerOfTwo<-7>();
constexpr auto c_015625 = internal::PowerOfTwo<-6>();
constexpr auto c_03125 = internal::PowerOfTwo<-5>();
constexpr auto c_0625 = internal::PowerOfTwo<-4>();
constexpr auto c_125 = internal::PowerOfTwo<-3>();
constexpr auto c_25 = internal::PowerOfTwo<-2>();
constexpr auto c_5 = internal::PowerOfTwo<-1>();
constexpr auto c1 = internal::PowerOfTwo<0>();
constexpr auto c2 = internal::PowerOfTwo<1>();
constexpr auto c4 = internal::PowerOfTwo<2>();
constexpr auto c8 = internal::PowerOfTwo<3>();
constexpr auto c16 = internal::PowerOfTwo<4>();
constexpr auto c32 = internal::PowerOfTwo<5>();
constexpr auto c64 = internal::PowerOfTwo<6>();
constexpr auto c128 = internal::PowerOfTwo<7>();
constexpr auto c256 = internal::PowerOfTwo<8>();
constexpr auto c512 = internal::PowerOfTwo<9>();
constexpr auto c1024 = internal::PowerOfTwo<10>();
constexpr auto c2048 = internal::PowerOfTwo<11>();
constexpr auto c4096 = internal::PowerOfTwo<12>();

// sqrt2   = 1.011_0101_0000_0100_11110011001100111111100111011110011001001000010001011001011111011000100110110011011
// sqrt2ub = 1.011_0101_0000_0101
// [dec]   = 1.414215087890625
constexpr auto sqrt2ub = Fixed<0, 1, 15>{ std::numbers::sqrt2 };

}
