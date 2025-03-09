#pragma once

#include <cstdint>

namespace numeric {

using i64 = std::int64_t;
using i32 = std::int32_t;
using i16 = std::int16_t;
using i8 = std::int8_t;
using u64 = std::uint64_t;
using u32 = std::uint32_t;
using u16 = std::uint16_t;
using u8 = std::uint8_t;

template<typename T>
concept IsRepr =
  std::is_same_v<std::remove_cvref_t<T>, i64> ||
  std::is_same_v<std::remove_cvref_t<T>, i32> ||
  std::is_same_v<std::remove_cvref_t<T>, i16> ||
  std::is_same_v<std::remove_cvref_t<T>, i8> ||
  std::is_same_v<std::remove_cvref_t<T>, u64> ||
  std::is_same_v<std::remove_cvref_t<T>, u32> ||
  std::is_same_v<std::remove_cvref_t<T>, u16> ||
  std::is_same_v<std::remove_cvref_t<T>, u8>;

template<typename T>
concept IsFloat =
  std::is_same_v<std::remove_cvref_t<T>, float> ||
  std::is_same_v<std::remove_cvref_t<T>, double>;

template<typename T>
concept IsReprOrFloat = IsRepr<T> || IsFloat<T>;

}
